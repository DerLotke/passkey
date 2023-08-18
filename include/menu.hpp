#pragma once

#include <widget.hpp>
#include <label.hpp>

#include <Arduino.h>
#include <list>
#include <vector>

namespace UI {
    class AbstractMenuBar
    {
        public:

        typedef std::vector<String> MenuItems;

        AbstractMenuBar(const MenuItems &menuItems,
                        unsigned selected = 0);
        
        virtual ~AbstractMenuBar();
        
        virtual void selectNext();
        virtual void selectPrevious();

        protected:

        MenuItems items_;
        unsigned selectedItem_;

        virtual unsigned itemsOnDisplay() const = 0;

        unsigned firstItemToDisplay() const;
        unsigned lastItemToDisplay() const;
        unsigned itemsToDraw() const;


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
            std::list<Label*> menuLabel_;
            Label *selectLabel_;
            Label *upLabel_;
            Label *downLabel_;

            void updateDisplayedLabels();
    };
}
