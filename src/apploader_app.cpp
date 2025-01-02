#include "apploader_app.hpp"
#include "config.hpp"

#include <functional>

AppLoaderApplication::AppLoaderApplication(std::initializer_list<AbstractAppItem*> appItems): UI::Application(),
    suspendedApp_(nullptr),
    doUnload_(false),
    doSuspend_(false)
{
}

AppLoaderApplication::~AppLoaderApplication()
{
}

void AppLoaderApplication::update()
{
    if (doUnload_)
    {
        unload();
        doUnload_ = false;
    }

    if (currentApp_)
    {
        currentApp_->update();
    }
    else
    {
        UI::Application::update(); // Call the update from the base class
    }
}


void AppLoaderApplication::load(unsigned index)
{
    currentApp_ = apps_.at(index)->create();
}


void AppLoaderApplication::unload()
{
    currentApp_.reset();
}


void AppLoaderApplication::onNotify(Widget* requestOrigin, UI::NotificationCode code)
{
    switch (code)
    {
        case UI::NotificationCode::DESTROY_ME:
            doUnload_ = true;
            break;
        case UI::NotificationCode::SUSPEND_ME:
            doSuspend_ = true;
            break;
    }
}

