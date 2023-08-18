#pragma once

#include <label.hpp>

namespace UI {
    class MenuItem : public Label
    {
        public:
            MenuItem(const String &item, unsigned width);
    };
}
