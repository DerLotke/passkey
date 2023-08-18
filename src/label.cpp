#include "label.hpp"

namespace UI
{
    Label::Label(const Rect &rect, const String &text, Widget * const parent):
        Widget(rect,parent),
        text_(text),
        textColor_(DefaultTextColor),
        drawTextColor_(DefaultTextColor),
        origFaceColor_(DefaultFaceColor),
        inverted_(false)
    {
    }
    
    void Label::setInverted(bool inverted) {
       
        if(inverted)
        {
            drawTextColor_ = origFaceColor_;
            faceColor_ = textColor_;
        } else
        {
            drawTextColor_ = textColor_;
            faceColor_ = origFaceColor_;
        }

        inverted_ = inverted;
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

        drawBuffer.setTextColor(drawTextColor_);
        drawBuffer.drawString(textToDraw, drawRect.x, drawRect.y);
    }
}
