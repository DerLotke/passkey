#pragma once

#define TOML_NO_OVERALIGN
#include <toml.hpp>

toml::table& getConfig();
void unloadConfig();
