#include "config.hpp"
#include "sdcard.hpp"

#include <string_view>
#include <ext/stdio_filebuf.h> 
#include <iostream>
#include <fstream>
#include <string>

constexpr std::string_view configFile_ = "passkey_config.toml";
static toml::table * loadedConfig_ = nullptr;

static toml::table defaultConfig() noexcept
{
    return toml::table{
	{"device", toml::table{
	    {"vendor_id", 0x413c},
	    {"product_id", 0x2010},
        }},
	{"keys", toml::table{
	    {"forward", "W"},
	    {"backward", "S"},
	    {"confirm", "ENTER"},
	    {"cancel", "ESC"},
	    {"select", "SHIFT"}
        }},
    };
}

toml::parse_result& getConfig()
{
    if (loadedConfig_ == nullptr)
    {
#if 0
	try
	{
	    SDCard& source = SDCard::load();
	    SDCard::SdCardFile file = source.open(
	        String(configFile_.data()),
		SDCard::OpenMode::FILE_READONLY);
	    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
	    std::istream is(&filebuf);
	    loadedConfig_ = new toml::table(std::move(toml::parse(is)));
	}
	catch (const toml::parse_error&)
	{
	    loadedConfig_ = new toml::table(std::move(defaultConfig()));
	}
#else
	loadedConfig_ = new toml::table(std::move(defaultConfig()));
#endif
    }
    return *loadedConfig_;
}
