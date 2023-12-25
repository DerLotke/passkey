#pragma once

#include "colors.hpp"
#include <map>
#include <Arduino.h>

namespace UI
{
    struct Theme {
        struct {
            Color background;
            Color text;
            Color highlight;
            Color border;
	} colors;
    };

    auto themes() -> std::map<String, Theme> const&;
}
