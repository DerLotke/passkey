#pragma  once

#include "widget.hpp"

namespace UI
{
    /* 
     * A DrawDelegator class contains elements that can be drawn,
     * but does not perform a draw action themselves.
     *
     * This class needs to be inherited by another class.
     * Also, the consumed drawable needs to be owned by inheritor.
     */ 
    class DrawDelegator : public Widget
    {
        public:
            DrawDelegator(Widget * const parent);

            virtual void redraw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override;
            virtual void draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const override;
    };
}
