#include <Arduino.h>
#include <TFT_eSPI.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

#include "ec1834.hpp"
#include "widget.hpp"
#include "label.hpp"
#include "application.hpp"


UI::Application *application;
UI::Label * newLabel;

void setup() {
  UI::Rect fullScreen = UI::Application::getFullFrameRect();
  application = new UI::Application();
  newLabel = new UI::Label(UI::Rect(1,1,fullScreen.width,1),"\260\261\262\333Hello World!\333\262\261\260", application);
}

unsigned count = 0;
void loop() {
  newLabel->setInverted(!newLabel->getInverted());
  application->update();

  delay(500);
  
}
