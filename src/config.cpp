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
    try
    {
        std::shared_ptr<SDCard> source = SDCard::load();
        SDCard::SdCardFile file = source->open(
    	String(configFileName().data()),
    	SDCard::OpenMode::FILE_READONLY);
        if (!file)
        {
    	    return std::make_shared<toml::table>(std::move(defaultConfig()));
        }
        __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
        std::istream is(&filebuf);
        return std::make_shared<toml::table>(std::move(toml::parse(is)));
    }
    catch (const toml::parse_error&)
    {
        return std::make_shared<toml::table>(std::move(defaultConfig()));
    }
}
