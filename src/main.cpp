#include <Arduino.h>
#include <TFT_eSPI.h>

#include <aes/esp_aes.h>
#include <sdcard.hpp>

#include <list>

#include "ec1834.hpp"
#include "widget.hpp"
#include "statusbar.hpp"
#include "application.hpp"
#include "menu.hpp"
#include "keyboard.hpp"

static UI::Application *application;
static UI::VerticalMenu *vmenu;
static Statusbar *statusBar;
static SDCard *sdCard;
static UI::AbstractMenuBar::MenuItems menuItems;
static UsbKeyboard *keyboard;

static void loadDirectoryContent(void)
{
  std::shared_ptr<DIR> directory = sdCard->openDir("");

  dirent *dir;
  while((dir = readdir(directory.get())))
  {
      if(DT_REG == dir->d_type) {
        menuItems.emplace_back(String(dir->d_name));
      }
  }

  if(menuItems.empty()) {
    menuItems.emplace_back(String("No Files found"));
  }
}

static void onMenuSelected(void *event_handler_arg,
                           esp_event_base_t event_base,
                           int32_t event_id,
                           void *event_data)
{
   if(event_base == MENU_EVENT)
   {
      UI::AbstractMenuBar::EventData *eventData = reinterpret_cast<UI::AbstractMenuBar::EventData*>(event_data);
      
      if(eventData)
      {
        if(eventData->self == vmenu)
        {
            KeyStrokeFile file(sdCard->open(vmenu->selectedItem(), SDCard::OpenMode::FILE_READONLY));
            keyboard->sendKeyStrokes(file);
        }
      }
   }
}

static void onLedUpdate(void *event_handler_arg,
                           esp_event_base_t event_base,
                           int32_t event_id,
                           void *event_data)
{
  if(event_base == KEYBOARD_EVENT && event_id == UsbKeyboard::LedsUpdated) {
      UsbKeyboard::EventData *event = reinterpret_cast<UsbKeyboard::EventData *>(event_data);
      if(event)
      {
          statusBar->setCapsLockStatus(event->self->isCapsLockSet());
          statusBar->setNumLockStatus(event->self->isNumLockSet());
          statusBar->setScrollLockStatus(event->self->isScrollLockSet());
      }
  }
}

void setup()
{
  esp_event_loop_create_default();
  esp_event_handler_register(MENU_EVENT,ESP_EVENT_ANY_ID, onMenuSelected, NULL);
  esp_event_handler_register(KEYBOARD_EVENT,UsbKeyboard::LedsUpdated, onLedUpdate, NULL);
  
  sdCard = new SDCard();
  loadDirectoryContent();
  UI::Rect fullScreen = UI::Application::getFullFrameRect();
  application = new UI::Application();
  statusBar = new Statusbar(0,application);
  vmenu = new UI::VerticalMenu(menuItems,
                               UI::Rect(0,1,fullScreen.width, fullScreen.height - 1),
                               0,
                               application);
  keyboard = new UsbKeyboard(false);
}

unsigned count = 0;
void loop() {
  keyboard->tick();

  application->update();

  delay(5);  
}
