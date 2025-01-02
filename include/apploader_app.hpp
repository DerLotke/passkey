#pragma once

#include "application.hpp"
#include "keyboard.hpp"
#include "menu.hpp"
#include "themes.hpp"

#include <memory>
#include <functional>

class AbstractAppItem
{
    protected:
        String name_;

    public:
        AbstractAppItem(String name)
        :   name_(name)
        {}

        String const& getName()
        {
            return name_;
        }

        virtual std::shared_ptr<UI::Application> create() = 0;
};


template <class ApplicationClass, class... Ts>
class AppItem : public AbstractAppItem
{
    private:
        std::tuple<Ts...> args_;

    public:
        AppItem(
            String const& name,
            Ts... applicationArgs)
            :   AbstractAppItem(name),
                args_(std::forward<Ts>(applicationArgs)...)
        {}

       virtual std::shared_ptr<UI::Application> create() override
       {
           return std::apply(std::make_shared<ApplicationClass, std::add_lvalue_reference_t<Ts>...>, args_);
       }
};


class AppLoaderApplication: public UI::Application
{
    public:
        AppLoaderApplication(std::initializer_list<AbstractAppItem*> appItems);
        virtual ~AppLoaderApplication();

        void update() override;

        void load(unsigned index = 0);
        void unload();

    protected:
        virtual void onNotify(Widget* requestOrigin, UI::NotificationCode code) override;


    private:
        std::vector<AbstractAppItem*> apps_; // Front is active app

        std::shared_ptr<UI::Application> currentApp_;
        AbstractAppItem* suspendedApp_;

        bool doUnload_;
        bool doSuspend_;
};

