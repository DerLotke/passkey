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


void setup() {
  esp_event_loop_create_default();
  sdCard = new SDCard();
  loadDirectoryContent();
  UI::Rect fullScreen = UI::Application::getFullFrameRect();
  application = new UI::Application();
  statusBar = new Statusbar(0,application);
  vmenu = new UI::VerticalMenu(menuItems,
                               UI::Rect(0,1,fullScreen.width, fullScreen.height - 1),
                               0,
                               application);
  keyboard = new UsbKeyboard(true);
}

unsigned count = 0;
void loop() {
  keyboard->tick();

  application->update();

  delay(5);  
}
