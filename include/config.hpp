#pragma once

#ifndef TOML_HEADER_ONLY
    #define TOML_HEADER_ONLY 0
#endif
#include <toml.hpp>

class SDCard;

toml::table& getConfig(SDCard const& source);
