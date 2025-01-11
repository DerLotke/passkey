#pragma once

#include <widget.hpp>
#include "keyboard.hpp"

namespace UI {
class Application: public Widget
{
    public:
        Application(Application * parent = nullptr);

        static Rect getFullFrameRect() {return Rect(0,0,TFT_HEIGHT,TFT_WIDTH).toLogical(); }

        virtual void update();

    protected:
        UsbKeyboard& keyboard_;
};
}
