#include <Arduino.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello World!");
  
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLUE);
  tft.setTextFont(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.println("Hello World!");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hello World!");
  delay(1000);
}
