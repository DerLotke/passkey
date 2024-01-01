#include "config.hpp"
#include "sdcard.hpp"

#include <string_view>
#include <ext/stdio_filebuf.h> 
#include <iostream>
#include <fstream>
#include <string>

static constexpr std::string_view configFile_ = "passkey_config.toml";
static toml::table * loadedConfig_ = nullptr;

static toml::table defaultConfig() noexcept
{
    return toml::table{
	{"device", toml::table{
	    {"vendor_id", 0x413c},
	    {"product_id", 0x2010},
        }},
    };
}

toml::parse_result& getConfig()
{
    if (loadedConfig_ == nullptr)
    {
	try
	{
	    SDCard& source = SDCard::load();
	    SDCard::SdCardFile file = source.open(
	        String(configFile_.data()),
		SDCard::OpenMode::FILE_READONLY);
	    if (!file)
	    {
		loadedConfig_ = new toml::table(std::move(defaultConfig()));
		return *loadedConfig_;
	    }
	    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
	    std::istream is(&filebuf);
	    loadedConfig_ = new toml::table(std::move(toml::parse(is)));
	}
	catch (const toml::parse_error&)
	{
	    loadedConfig_ = new toml::table(std::move(defaultConfig()));
	}
    }
    return *loadedConfig_;
}


void unloadConfig()
{
    if (loadedConfig_ != nullptr)
    {
	delete loadedConfig_;
	loadedConfig_ = nullptr;
    }
}


std::string_view configFileName()
{
    return configFile_;
}
