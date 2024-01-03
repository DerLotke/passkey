#pragma once

#define TOML_NO_OVERALIGN
#include <toml.hpp>
#include <string_view>

/**
 * @brief Acquire the configuration file.
 *
 * This function attempts to load the SD card
 * and retrieve the configuration file.
 **/
std::shared_ptr<toml::table const> getConfig();

/**
 * @brief Returns the expected filename of the configuration file.
 **/
constexpr std::string_view configFileName() {return "passkey_config.toml";}
