#pragma once

#include <menuItem.hpp>
#include <widget.hpp>
#include <rect.hpp>
#include <list>

namespace UI {
    class AbstractMenuBar : public Widget
    {
        public:

        AbstractMenuBar(const Rect &area, Widget * const parent = nullptr);
        
        protected:
        std::list<MenuItem> items;

        void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override = 0;

    };
}
