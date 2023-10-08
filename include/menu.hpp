#pragma once

#include <widget.hpp>
#include <label.hpp>
#include <keyboard.hpp>

#include <Arduino.h>
#include <list>
#include <vector>
#include <memory>

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

    class VerticalMenu: public AbstractMenuBar, public Widget
    {
        public:
            VerticalMenu(const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        unsigned selected,
                        Widget * const parent
                        );

            ~VerticalMenu();
            
            void selectNext() override;
            void selectPrevious() override;
            unsigned itemsOnDisplay() const override;

        private:
            std::list<std::shared_ptr<Label> > menuLabel_;
            std::shared_ptr<Label> selectLabel_;
            std::shared_ptr<Label> upLabel_;
            std::shared_ptr<Label> downLabel_;

            void updateDisplayedLabels();
    };
}
