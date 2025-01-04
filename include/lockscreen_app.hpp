#pragma once

#include "application.hpp"
#include "image.hpp"

class LockscreenApplication: public UI::Application
{
    public:
        LockscreenApplication(UI::Application * parent = nullptr);
        virtual ~LockscreenApplication();

        void update() override;
        virtual void onKeyboardEvent(int32_t eventId, UsbKeyboard::EventData const * event) override;

    private:
        UI::Image imageWidget_;
        bool capsLockSet_;
        bool numLockSet_;
        bool scrollLockSet_;
        unsigned ticksForSimultaneousPress_;
};
