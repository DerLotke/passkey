#include "menu.hpp"

ESP_EVENT_DEFINE_BASE(MENU_EVENT);

namespace UI
{
    AbstractMenuBar::AbstractMenuBar(
		    	const AbstractMenuBar::MenuItems &menuItems,
                        Rect area,
                        unsigned selected,
                        Widget * const parent) :
	    		    Widget(area, parent),
                            items_(menuItems),
                            selectedItem_(selected)
    {
        esp_event_handler_register(KEYBOARD_EVENT,
                                   ESP_EVENT_ANY_ID,
                                   AbstractMenuBar::keyboardEventHandler,
                                   this);
    }

    AbstractMenuBar::~AbstractMenuBar()
    {
        esp_event_handler_unregister(KEYBOARD_EVENT,
                                     ESP_EVENT_ANY_ID,
                                     AbstractMenuBar::keyboardEventHandler);
    }

    unsigned AbstractMenuBar::firstItemToDisplay() const
    {
        unsigned const displayed = itemsOnDisplay();
        unsigned displayedBefore = (displayed - 1) / 2;
        unsigned first = selectedItem_ > displayedBefore ? selectedItem_ - displayedBefore : 0;

        if (first + displayed >= items_.size())
        {
            unsigned over = (first + displayed) - items_.size();
            first = first >= over ? first - over : 0;
        }

        return first;
    }


    unsigned AbstractMenuBar::lastItemToDisplay() const
    {
        unsigned const displayedAfter = firstItemToDisplay() + itemsOnDisplay() - 1;
        return items_.size() > displayedAfter ? displayedAfter : items_.size() - 1;

    }

    unsigned AbstractMenuBar::itemsToDraw() const
    {
        return lastItemToDisplay() - firstItemToDisplay();
    }

    void AbstractMenuBar::selectNext()
    {
        selectedItem_ = (selectedItem_ + 1) % items_.size();
    }

    void AbstractMenuBar::selectPrevious()
    {
        if (selectedItem_ == 0) {
            selectedItem_ = items_.size() - 1;
        } else {
            --selectedItem_;
        }
    }

    void AbstractMenuBar::entryChoosen()
    {
        EventData data;
        data.self = this;
        esp_event_post(MENU_EVENT, ItemSelected, &data, sizeof(EventData), 0);
    }


    void AbstractMenuBar::onKeyboardEvent(UsbKeyboard::Events event)
    {
        switch (event)
        {
        case UsbKeyboard::KeyDown:   selectNext(); break;
        case UsbKeyboard::KeyUp: selectPrevious(); break;
        case UsbKeyboard::KeySelect: entryChoosen(); break;

        default:
            break;
        }
    }

    void AbstractMenuBar::keyboardEventHandler( void* event_handler_arg,
                                                esp_event_base_t event_base,
                                                int32_t event_id,
                                                void* event_data)
    {
        if(event_handler_arg)
        {
            AbstractMenuBar *self = reinterpret_cast<AbstractMenuBar*>(event_handler_arg);

            if(KEYBOARD_EVENT == event_base) {
                self->onKeyboardEvent(static_cast<UsbKeyboard::Events>(event_id));
            }
        }
    }

} // namespace UI
