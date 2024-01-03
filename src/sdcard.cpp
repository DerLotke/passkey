#include "sdcard.hpp"

#include <esp_vfs_fat.h>
#include <sdmmc_cmd.h>
#include <driver/sdmmc_host.h>

#include <ext/stdio_filebuf.h> 
#include <istream>
#include <iostream>


/* Hardware Config given here */
constexpr gpio_num_t SD_MMC_D0_PIN() { return GPIO_NUM_14; }
constexpr gpio_num_t SD_MMC_D1_PIN() { return GPIO_NUM_17; }
constexpr gpio_num_t SD_MMC_D2_PIN() { return GPIO_NUM_21; }
constexpr gpio_num_t SD_MMC_D3_PIN() { return GPIO_NUM_18; }
constexpr gpio_num_t SD_MMC_CLK_PIN() { return GPIO_NUM_12; }
constexpr gpio_num_t SD_MMC_CMD_PIN() { return GPIO_NUM_16; }


std::mutex SDCard::mutex_;


constexpr const char *mountPoint()
{
    return "/sdcard";
}

/*This construct is used to hide the C API from the user ... stupid implementation von espressif ...*/
struct SdCardData : public sdmmc_card_t
{
};


SDCard::SDCard() : card_(nullptr),
                   sdcardOk_(false)
{
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024};

    /* Load the default values, so we only need to overwrite the necessary once */
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();

    host.flags = SDMMC_HOST_FLAG_4BIT | SDMMC_HOST_FLAG_DDR;

    slot_config.clk = SD_MMC_CLK_PIN();
    slot_config.cmd = SD_MMC_CMD_PIN();
    slot_config.d0 = SD_MMC_D0_PIN();
    slot_config.d1 = SD_MMC_D1_PIN();
    slot_config.d2 = SD_MMC_D2_PIN();
    slot_config.d3 = SD_MMC_D3_PIN();
    slot_config.width = 4;
    slot_config.flags |= SDMMC_SLOT_FLAG_INTERNAL_PULLUP;

    sdcardOk_ = ESP_OK == esp_vfs_fat_sdmmc_mount(mountPoint(),
                                                  &host,
                                                  &slot_config,
                                                  &mount_config,
                                                  reinterpret_cast<sdmmc_card_t **>(&card_));
}

SDCard::~SDCard()
{
    std::scoped_lock(mutex_);
    if (sdcardOk_ && card_)
    {
        esp_vfs_fat_sdcard_unmount(mountPoint(), card_);
    }
}

SDCard::SdCardFile SDCard::open(const String &filename, OpenMode const mode) const
{
    std::scoped_lock(mutex_);
    SdCardFile result;

    if (sdcardOk_)
    {
        String path(mountPoint());
        path += "/";
        path += filename;

        result = SdCardFile(fopen(path.c_str(),
                                  SDCard::OpenMode::FILE_READWRITE == mode ? "w+b" : "rb"),
                            fclose);
    }

    return result;
}

SDCard::SdCardDirectory SDCard::openDir(const String &pathName)
{
    std::scoped_lock(mutex_);

    SdCardDirectory result;

    if(sdcardOk_)
    {
        String path(mountPoint());
        path += "/";
        path += pathName;

        result = SdCardDirectory(opendir(path.c_str()), closedir);
    }

    return result;
}


template<>
void SDCard::openFileStream<std::istream>(String const& filename, std::function<void(std::istream&)> op)
{
    SDCard::SdCardFile file = this->open(
        filename,
        SDCard::OpenMode::FILE_READONLY
    );
    if (!file)
    {
	std::istream is(nullptr);
        op(is);
	return;
    }
    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
    std::istream is(&filebuf);
    op(is);
}


template<>
void SDCard::openFileStream<std::iostream>(String const& filename, std::function<void(std::iostream&)> op)
{
    SDCard::SdCardFile file = this->open(
        filename,
        SDCard::OpenMode::FILE_READWRITE
    );
    if (!file)
    {
	std::iostream ios(nullptr);
        op(ios);
	return;
    }
    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in | std::ios::out);
    std::iostream ios(&filebuf);
    op(ios);
}


std::shared_ptr<SDCard> SDCard::load()
{
    std::scoped_lock(mutex_);

    static std::shared_ptr<SDCard> sdCard(nullptr);
    if (!sdCard)
    {
	// Can't use make_unique here because
	// the constructor is private and
	// making the shared_ptr a friend
	// doesn't help
	sdCard = std::shared_ptr<SDCard>(new SDCard());
    }
    return sdCard;
}
