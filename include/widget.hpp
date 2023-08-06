#pragma once

#include <TFT_eSPI.h>

#include <rect.hpp>


namespace UI {
    class Widget
    {
        public:
        Widget(const Rect &area, Widget * const parent = nullptr);
        virtual ~Widget();

        virtual void redraw(TFT_eSprite &drawBuffer, const Rect &clientArea) const;
        
        protected:
        virtual void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const;
        
        Rect area_;
        Widget * parent_;
        Widget * child_;
        Widget * nextSibbling_;
    };
}
