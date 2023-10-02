#include "sdcard.hpp"

#include <esp_vfs_fat.h>
#include <sdmmc_cmd.h>
#include <driver/sdmmc_host.h>

/* Hardware Config given here */
constexpr gpio_num_t SD_MMC_D0_PIN() { return GPIO_NUM_14; }
constexpr gpio_num_t SD_MMC_D1_PIN() { return GPIO_NUM_17; }
constexpr gpio_num_t SD_MMC_D2_PIN() { return GPIO_NUM_21; }
constexpr gpio_num_t SD_MMC_D3_PIN() { return GPIO_NUM_18; }
constexpr gpio_num_t SD_MMC_CLK_PIN() { return GPIO_NUM_12; }
constexpr gpio_num_t SD_MMC_CMD_PIN() { return GPIO_NUM_16; }

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
    if (sdcardOk_ && card_)
    {
        esp_vfs_fat_sdcard_unmount(mountPoint(), card_);
    }
}

std::shared_ptr<FILE> SDCard::open(const String &filename, OpenMode const mode)
{
    std::shared_ptr<FILE> result;

    if (sdcardOk_)
    {
        String path(mountPoint());
        path += "/";
        path += filename;

        result = std::shared_ptr<FILE>(fopen(path.c_str(),
                                             SDCard::OpenMode::FILE_READWRITE == mode ? "w+b" : "rb"),
                                       fclose);
    }

    return result;
}

std::shared_ptr<DIR> SDCard::openDir(const String &pathName)
{
    std::shared_ptr<DIR> result;

    if(sdcardOk_)
    {
        String path(mountPoint());
        path += "/";
        path += pathName;

        result = std::shared_ptr<DIR>(opendir(path.c_str()), closedir);
    }

    return result;
}
