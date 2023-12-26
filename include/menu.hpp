#pragma once

#include <widget.hpp>
#include <label.hpp>
#include <keyboard.hpp>
#include <themes.hpp>

#include <Arduino.h>
#include <list>
#include <vector>
#include <memory>
#include <functional>

#include <esp_event.h>

ESP_EVENT_DECLARE_BASE(MENU_EVENT);

namespace UI {
    class AbstractMenuBar
    {
        public:

        enum Events{
            ItemSelected
        };

        struct EventData
        {
            AbstractMenuBar *self;
        };

        typedef std::vector<String> MenuItems;

        AbstractMenuBar(const MenuItems &menuItems,
                        unsigned selected = 0);

        virtual ~AbstractMenuBar();

        virtual void selectNext();
        virtual void selectPrevious();
        virtual void entryChoosen();
        virtual String selectedItem() const { return items_[selectedItem_]; }
        virtual unsigned selectedIndex() const {return selectedItem_; }

        protected:

        MenuItems items_;
        unsigned selectedItem_;


        virtual unsigned itemsOnDisplay() const = 0;

        unsigned firstItemToDisplay() const;
        unsigned lastItemToDisplay() const;
        unsigned itemsToDraw() const;

        private:
        void onKeyboardEvent(UsbKeyboard::Events event);
        static void keyboardEventHandler( void* event_handler_arg, esp_event_base_t event_base,  int32_t event_id, void* event_data);

    };

    class Menu
    {
	using EventHandler = typename std::function<
	    void(AbstractMenuBar&, UI::AbstractMenuBar::EventData const&)
	>;
	public:
	    template<class MenuBarClass, class... Args>
	    Menu(
		EventHandler menuEventHandler,
		Widget * const parent,
		Args... menuBarArgs) :
		    menuBar_(std::move(
			std::make_unique<MenuBarClass>(menuBarArgs..., this))),
		    menuEventHandler_(menuEventHandler),
		    parent_(parent) {}
	    
	    ~Menu();

	private:
	    std::unique_ptr<AbstractMenuBar> menuBar_;
	    EventHandler menuEventHandler_;
	    Widget * const parent_;

	    void onEvent(
	        void *event_handler_arg,
        	esp_event_base_t event_base,
                int32_t event_id,
                void *event_data);
    };

    class VerticalMenuBar: public AbstractMenuBar, public Widget
    {
        public:
            explicit VerticalMenuBar(const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        unsigned selected,
                        Widget * const parent
                        );
            explicit VerticalMenuBar(const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        Theme const& theme,
                        unsigned selected,
                        Widget * const parent
                        );

            ~VerticalMenuBar();

            void selectNext() override;
            void selectPrevious() override;
            unsigned itemsOnDisplay() const override;

            void setTheme(Theme const& theme) override;

        private:
            std::list<std::shared_ptr<Label> > menuLabel_;
            std::shared_ptr<Label> selectLabel_;
            std::shared_ptr<Label> upLabel_;
            std::shared_ptr<Label> downLabel_;

            void updateDisplayedLabels();
    };
}
