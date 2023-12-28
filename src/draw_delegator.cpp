#include "draw_delegator.hpp"
#include "widget.hpp"

using namespace UI;

DrawDelegator::DrawDelegator(Widget * const parent) :
    Widget(Rect(), parent)
{
    // empty
}

void DrawDelegator::redraw(TFT_eSprite &drawBuffer, const Rect &clientArea) const
{
    if (hidden_) return;

    Widget const * child = child_;
    while (child) {
        child->redraw(drawBuffer, clientArea);
        child = child->getSibling();
    }
}

void DrawDelegator::draw(TFT_eSprite&, const Rect&) const
{
    // no-op
}
