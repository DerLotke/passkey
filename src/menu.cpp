#include "menu.hpp"

using namespace UI;

std::set<Menu*> Menu::menus_;

void UI::espMenuEventHandler(
    void *event_handler_arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data)
{
    // Use this to delegate the call because
    // a bound member function cannot be used in place
    // of a function ptr
    for (Menu* menu : Menu::menus_)
    {
        menu->onEvent(event_handler_arg, event_base, event_id, event_data);
    }
};


Menu::~Menu()
{
#if 0
	if (parent_) {
	    Widget * previousChild = nullptr;
	    Widget * child = parent_->child_;

	    while(child && child != this) {
		previousChild = child;
		child = child ->nextSibbling_;
	    }

	    if(previousChild && child) {
		previousChild ->nextSibbling_ = nextSibbling_;
	    } else if( child ) {
		parent_->child_ = nextSibbling_;
	    } // else the child was not found which would be an
	      // inconsistency error and should never happen
	}
#endif
	menus_.erase(this);
}


void Menu::onEvent(
    void *event_handler_arg,
    esp_event_base_t event_base,
    int32_t event_id,
    void *event_data)
{
    if (event_base == MENU_EVENT)
    {
	UI::AbstractMenuBar::EventData *eventData =
	    reinterpret_cast<UI::AbstractMenuBar::EventData*>(event_data);

      	if (eventData && eventData->self == menuBar_.get())
      	{
   	    menuEventHandler_(*menuBar_, *eventData);
      	}
   }
}


void Menu::makeActive()
{
    for (Menu* menu : menus_)
    {
	menu->menuBar_->setHidden(true);
    }
    menuBar_->setHidden(false);
}
