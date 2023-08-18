#include <Arduino.h>
#include <TFT_eSPI.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

#include <list>

#include "ec1834.hpp"
#include "widget.hpp"
#include "statusbar.hpp"
#include "application.hpp"

UI::Application *application;
Statusbar *statusBar;

void setup() {
  UI::Rect fullScreen = UI::Application::getFullFrameRect();
  application = new UI::Application();
  statusBar = new Statusbar(0,application);
}

unsigned count = 0;
void loop() {
  application->update();

  delay(500);  
}
