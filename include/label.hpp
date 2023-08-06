#pragma once

#include <widget.hpp>
#include <Arduino.h>

namespace UI
{
    class Label : public Widget
    {
        public:
        Label(const Rect &rect, const String &text, Widget * const parent = nullptr);

        protected:

        String text_;

        void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override;

    };
}