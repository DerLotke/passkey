#pragma once

#include "application.hpp"
#include "image.hpp"

class LockscreenApplication: public UI::Application
{
    public:
        LockscreenApplication(UI::Application * parent = nullptr);
        virtual ~LockscreenApplication();

        virtual void onKeyboardEvent(int32_t eventId, UsbKeyboard::EventData const * event) override;

    private:
        UI::Image imageWidget_;
};
