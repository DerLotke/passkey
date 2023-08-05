#include <Arduino.h>
#include <TFT_eSPI.h>

#include "ec1834.hpp"

TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World!");
  
  tft.init();
  tft.setAttribute(UTF8_SWITCH,0);
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  ec1834bin_select(tft);
  
  tft.setCursor(2,2);
  tft.printf("\260\261\262\333           \333\262\261\260");
  tft.setTextColor(TFT_BLACK,TFT_GREEN);
  tft.drawString(" Hello 000 ",4*8+2,2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.printf("");
  tft.setTextColor(TFT_BROWN, TFT_BLACK);
  tft.printf("\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337\337");
  tft.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
  tft.printf("This is using the original EC1834 font ROM");  
}
unsigned count = 0;
void loop() {
  // put your main code here, to run repeatedly:
  tft.setTextColor(TFT_BLACK,TFT_GREEN);
  tft.drawString("   ",11*8+2,2);
  tft.drawNumber(count%1000,11*8+2,2);
  ++count;
  delay(500);
}
