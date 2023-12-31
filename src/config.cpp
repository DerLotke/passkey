#define TOML_IMPLEMENTATION
#include <toml.hpp> // Compile toml library in this compilation unit

#include "config.hpp"
#include "sdcard.hpp"

#include <string_view>
#include <ext/stdio_filebuf.h> 
#include <iostream>
#include <fstream>
#include <string>


using namespace std::literals::string_view_literals;

constexpr std::string_view configFile_ = "passkey_config.toml";
static toml::table * loadedConfig_ = nullptr;

static toml::table defaultConfig() noexcept
{
    return toml::parse(R"(
[device]
vendor_id = 0x413c
product_id = 0x2010

[keys]
forward = "W"
backward = "S"
confirm = "ENTER"
cancel = "ESC"
select = "SHIFT"

)"sv);
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
	    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
	    std::istream is(&filebuf);
	    *loadedConfig_ = toml::parse(is);
	}
	catch (const toml::parse_error&)
	{
	    *loadedConfig_ = defaultConfig();
	}
    }
    return *loadedConfig_;
}
