#pragma once

#include <widget.hpp>
#include <Arduino.h>
#include <colors.hpp>

namespace UI
{
    class Label : public Widget
    {
        public:
        Label(const Rect &rect, const String &text, Widget * const parent = nullptr);

        void setTextColor(Color color) { textColor_ = color; }
        Color getTextColor() const { return textColor_; }
        
        void setInverted(bool inverted);
        bool getInverted() const { return inverted_; }

        protected:

        String text_;
        Color textColor_;
        bool inverted_;

        void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override;

    };
}