#pragma once

#include <label.hpp>
#include <widget.hpp>

class Statusbar: public UI::Widget
{
    public:
        Statusbar(int const pos, Widget * const parent = nullptr);

        void setScrollLockStatus(bool enable) { scrollLockLabel_.setInverted(enable);}
        bool getScrollLockStatus() const { return scrollLockLabel_.getInverted(); }
        void setCapsLockStatus(bool enable) { capsLockLabel_.setInverted(enable); }
        bool getCapsLockStatus() const { return capsLockLabel_.getInverted(); }
        void setNumLockStatus(bool enable) { numLockLabel_.setInverted(enable); }
        bool getNumLockStatus() const { return numLockLabel_.getInverted(); }
    
    protected:
        UI::Label statusText_;
        UI::Label scrollLockLabel_;
        UI::Label numLockLabel_;
        UI::Label capsLockLabel_;
};