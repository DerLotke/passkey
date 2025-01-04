#include "image.hpp"

namespace UI
{

Image::Image(
    unsigned posX, unsigned posY,
    unsigned width, unsigned height,
    uint16_t const * data,
    Widget * const parent) :
        UI::Widget(UI::Rect(posX, posY, width, height), parent),
        data_(data)
{}


void Image::draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const
{
    Widget::draw(drawBuffer, clientArea);
    drawBuffer.pushImage(area_.x, area_.y, area_.width, area_.height, data_);
}

} // namespace UI
