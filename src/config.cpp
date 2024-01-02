#include "config.hpp"
#include "sdcard.hpp"

#include <string_view>
#include <ext/stdio_filebuf.h> 
#include <iostream>
#include <fstream>
#include <string>

static toml::table loadedConfig_;
static bool configLoaded_ = false;

static toml::table defaultConfig() noexcept
{
    return toml::table{
	{"device", toml::table{
	    {"vendor_id", 0x413c},
	    {"product_id", 0x2010},
        }},
    };
}

toml::table const& getConfig()
{
    if (!configLoaded_)
    {
	try
	{
	    SDCard& source = SDCard::load();
	    SDCard::SdCardFile file = source.open(
	        String(configFileName().data()),
		SDCard::OpenMode::FILE_READONLY);
	    if (!file)
	    {
		loadedConfig_ = std::move(toml::table(std::move(defaultConfig())));
		return loadedConfig_;
	    }
	    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
	    std::istream is(&filebuf);
	    loadedConfig_ = std::move(toml::table(std::move(toml::parse(is))));
	}
	catch (const toml::parse_error&)
	{
	    loadedConfig_ = std::move(toml::table(std::move(defaultConfig())));
	}
	configLoaded_ = true;
    }
    return loadedConfig_;
}
