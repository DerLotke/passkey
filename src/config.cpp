#include "config.hpp"
#include "sdcard.hpp"

#include <string_view>
#include <ext/stdio_filebuf.h> 
#include <iostream>
#include <fstream>
#include <memory>


static toml::table defaultConfig() noexcept
{
    return toml::table{
	{"device", toml::table{
	    {"vendor_id", 0x413c},
	    {"product_id", 0x2010},
        }},
    };
}

std::shared_ptr<toml::table const> getConfig()
{
    static std::shared_ptr<toml::table const> loadedConfig_(nullptr);
    if (!loadedConfig_)
    {
	try
	{
	    std::shared_ptr<SDCard> source = SDCard::load();
	    SDCard::SdCardFile file = source->open(
	        String(configFileName().data()),
		SDCard::OpenMode::FILE_READONLY);
	    if (!file)
	    {
		loadedConfig_ = std::make_shared<toml::table>(std::move(defaultConfig()));
		return loadedConfig_;
	    }
	    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
	    std::istream is(&filebuf);
	    loadedConfig_ = std::make_shared<toml::table>(std::move(toml::parse(is)));
	}
	catch (const toml::parse_error&)
	{
	    loadedConfig_ = std::make_shared<toml::table>(std::move(defaultConfig()));
	}
    }
    return loadedConfig_;
}
