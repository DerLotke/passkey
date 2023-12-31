#pragma once

#ifndef TOML_HEADER_ONLY
    #define TOML_HEADER_ONLY 0
#endif
#include <toml.hpp>

toml::table& getConfig();
