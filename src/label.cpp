#include "label.hpp"

namespace UI
{
    Label::Label(const Rect &rect, const String &text, Widget * const parent):
        Widget(rect,parent),
        text_(text)
    {
    }

    void Label::draw(TFT_eSprite &drawBuffer, const Rect &clientArea) const
    {
        Widget::draw(drawBuffer, clientArea);
        const String textToDraw = text_.substring(0,
                clientArea.width < text_.length()? 
                clientArea.width : 
                text_.length()
                );
        const Rect drawRect = clientArea.toScreen();

        drawBuffer.drawString(textToDraw, drawRect.x, drawRect.y);
    }
}
