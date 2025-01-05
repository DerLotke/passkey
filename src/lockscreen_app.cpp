#include "lockscreen_app.hpp"
#include "lockscreen_image.h"

static unsigned TICKS_FOR_SIMULTANEOUS_PRESS = 50;


LockscreenApplication::LockscreenApplication(Application * parent) :
    UI::Application(parent),
    imageWidget_(0, 0, TFT_HEIGHT, TFT_WIDTH, (uint16_t*)lockscreen_image, this),
    capsLockSet_(false),
    numLockSet_(false),
    scrollLockSet_(false),
    ticksForSimultaneousPress_(TICKS_FOR_SIMULTANEOUS_PRESS)
{}


LockscreenApplication::~LockscreenApplication()
{}


void LockscreenApplication::update()
{
    UI::Application::update(); // Call the update from the base class
    if (capsLockSet_ || numLockSet_ || scrollLockSet_)
    {
        --ticksForSimultaneousPress_;
    }

    if (ticksForSimultaneousPress_ == 0)
    {
        ticksForSimultaneousPress_ = TICKS_FOR_SIMULTANEOUS_PRESS;
        capsLockSet_ = false;
        numLockSet_ = false;
        scrollLockSet_ = false;
    }
}


void LockscreenApplication::onKeyboardEvent(int32_t eventId, UsbKeyboard::EventData const * event)
{
    if (eventId == UsbKeyboard::LedsUpdated && event)
    {
        if (event->self->isCapsLockSet())
        {
            capsLockSet_ = true;
        }
        if (event->self->isNumLockSet())
        {
            numLockSet_ = true;
        }
        if (event->self->isScrollLockSet())
        {
            scrollLockSet_ = true;
        }

        unsigned unlocksCounter = 0;
        if (capsLockSet_) ++unlocksCounter;
        if (numLockSet_) ++unlocksCounter;
        if (scrollLockSet_) ++unlocksCounter;

        if (unlocksCounter >= 2)
        {
            notifyParent(UI::NotificationCode::DESTROY_ME);
        }
    }
}
