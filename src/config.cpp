#include "config.hpp"
#include "sdcard.hpp"

#include <string_view>
#include <istream>
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
	std::shared_ptr<toml::table> tablePointer(nullptr);
        source->openFileStream<std::istream>(
	    String(configFileName().data()),
	    [&tablePointer](std::istream& is){
	        if (is.peek() == EOF)
		{
		    tablePointer = std::make_shared<toml::table>(
		        std::move(defaultConfig())
		    );
		}
		else
		{
		    tablePointer = std::make_shared<toml::table>(
		        std::move(toml::parse(is))
		    );
		}
	    }
	);
        return tablePointer;
    }
    catch (const toml::parse_error&)
    {
        return std::make_shared<toml::table>(std::move(defaultConfig()));
    }
}
