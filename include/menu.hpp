#pragma once

#include <widget.hpp>
#include <label.hpp>

#include <Arduino.h>
#include <list>

namespace UI {
    class AbstractMenuBar
    {
        public:

        AbstractMenuBar(const std::list<String> &menuItems,
                        unsigned selected = 0);
        
        virtual ~AbstractMenuBar();
        
        virtual void selectNext();
        virtual void selectPrevious();

        protected:

        std::list<String> items_;
        unsigned selectedItem_;

        virtual unsigned itemsOnDisplay() const = 0;

        unsigned firstItemToDisplay() const;
        unsigned lastItemToDisplay() const;
        unsigned itemsToDraw() const;


    };
}
