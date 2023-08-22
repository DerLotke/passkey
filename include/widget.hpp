#pragma once

#include <TFT_eSPI.h>

#include <rect.hpp>
#include <colors.hpp>


namespace UI {
    class Widget
    {
        public:
        Widget(const Rect &area, Widget * const parent = nullptr);
        virtual ~Widget();

        virtual void redraw(TFT_eSprite &drawBuffer, const Rect &clientArea) const;
        void setFaceColor(Color color) { faceColor_ = color; }
        Color getFaceColor() const { return faceColor_; }

        void moveTo(int x, int y) { area_.x = x; area_.y = y; }
        
        protected:
        virtual void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const;
        
        Rect area_;
        Widget * parent_;
        Widget * child_;
        Widget * nextSibbling_;
        Color faceColor_;
    };
}
