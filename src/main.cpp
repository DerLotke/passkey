#include <Arduino.h>
#include <TFT_eSPI.h>
#include <USB.h>
#include <USBHIDKeyboard.h>

#include "ec1834.hpp"
#include "widget.hpp"
#include "label.hpp"


static TFT_eSPI tft = TFT_eSPI();
static TFT_eSprite backBuffer(&tft);
static UI::Rect fullScreen(0,0,20,5);

UI::Widget application(UI::Rect(0,0,TFT_HEIGHT,TFT_WIDTH));
UI::Label * newLabel;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World!");
  
  tft.init();
  backBuffer.createSprite(160, 80);
  backBuffer.setAttribute(UTF8_SWITCH,0);
  backBuffer.fillScreen(TFT_BLACK);
  backBuffer.setTextColor(TFT_GREEN, TFT_BLACK);
  ec1834bin_select(backBuffer);

  tft.setAttribute(UTF8_SWITCH,0); 
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  ec1834bin_select(tft);
  
  newLabel = new UI::Label(UI::Rect(1,1,fullScreen.width,1),"\260\261\262\333Hello World!\333\262\261\260", &application);
}
unsigned count = 0;
void loop() {
  newLabel->setInverted(!newLabel->getInverted());
  backBuffer.fillRect(0,0,160,80,TFT_BLUE);
  backBuffer.setTextColor(TFT_LIGHTGREY);

  application.redraw(backBuffer, fullScreen);
  backBuffer.pushSprite(0,0);

  delay(500);
  
}
