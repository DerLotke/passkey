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

constexpr std::string_view configFile_ = "config.toml";
static toml::table * loadedConfig_ = nullptr;

static toml::table writeConfig() noexcept
{
    return toml::parse(R"(

[keys]
forward = "W"
back = "S"
confirm = "ENTER"
cancel = "ESC"

)"sv);
}

toml::parse_result& getConfig(SDCard const& source)
{
    if (loadedConfig_ == nullptr)
    {
	try
	{
	    auto file = source.open(
	        String(configFile_.data()),
		SDCard::OpenMode::FILE_READWRITE);
	    __gnu_cxx::stdio_filebuf<char> filebuf(file.get(), std::ios::in);
	    std::istream is(&filebuf);
	    *loadedConfig_ = toml::parse(is);
	}
	catch (const toml::parse_error&)
	{
	    *loadedConfig_ = writeConfig();
	}
    }
    return *loadedConfig_;
}
