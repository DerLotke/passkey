#pragma once

#define TOML_NO_OVERALIGN
#include <toml.hpp>
#include <string_view>

toml::table& getConfig();
void unloadConfig();

std::string_view configFileName();
