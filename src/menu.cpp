#include "menu.hpp"

using namespace UI;
#if 0
Menu::Menu(
    AbstractMenuBar const& menuBar,
    Menu::EventHandler menuEventHandler) :
	menuBar_(menuBar),
	menuEventHandler_(menuEventHandler)
{ /*empty*/ }
#endif

Menu::~Menu()
{

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
