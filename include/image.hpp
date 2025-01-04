#pragma once

#include <widget.hpp>

namespace UI
{

class Image : public UI::Widget
{
    public:
        explicit Image(
            unsigned posX, unsigned posY,
            unsigned width, unsigned height,
            uint16_t const * data,
            Widget * const parent = nullptr);

    protected:
        void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override;

    private:
        uint16_t const * data_;
};

} // namespace UI
