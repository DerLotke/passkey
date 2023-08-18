#include <Arduino.h>
#include <TFT_eSPI.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

#include <list>

#include "ec1834.hpp"
#include "widget.hpp"
#include "statusbar.hpp"
#include "application.hpp"
#include "menu.hpp"

UI::Application *application;
UI::VerticalMenu *vmenu;
Statusbar *statusBar;

static const UI::AbstractMenuBar::MenuItems menuItems = {"Entry 1", "Entry 2", "Entry 3", "Entry 4", "Entry 5", "Entry 6",
                                                         "Entry 7", "Entry 8", "Entry 9", "Entry 10"};


void setup() {
  UI::Rect fullScreen = UI::Application::getFullFrameRect();
  application = new UI::Application();
  statusBar = new Statusbar(0,application);
  vmenu = new UI::VerticalMenu(menuItems,
                               UI::Rect(0,1,fullScreen.width, fullScreen.height - 1),
                               0,
                               application);
}

unsigned count = 0;
void loop() {
  application->update();
  delay(500);
  vmenu->selectNext();
}
