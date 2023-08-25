#include <Arduino.h>
#include <TFT_eSPI.h>
#include <USB.h>
#include <USBHIDKeyboard.h>
#include <OneButton.h>

#include <aes/esp_aes.h>
#include <sdcard.hpp>
#include <USBCDC.h>
#include <HWCDC.h>

#include <list>

#include "ec1834.hpp"
#include "widget.hpp"
#include "statusbar.hpp"
#include "application.hpp"
#include "menu.hpp"

static UI::Application *application;
static UI::VerticalMenu *vmenu;
static Statusbar *statusBar;
static SDCard *sdCard;
static USBHIDKeyboard keyBoard;
static HWCDC hwcdc;
static USBCDC usbcdc;
static UI::AbstractMenuBar::MenuItems menuItems;
static OneButton btn = OneButton(0, true );        // Button is active LOW

arduino_usb_hid_keyboard_event_data_t leds_;

void myEventHandler( void* event_handler_arg,
                     esp_event_base_t event_base,
                     int32_t event_id,
                     void* event_data)
{
    if (ARDUINO_USB_HID_KEYBOARD_EVENTS == event_base  && ARDUINO_USB_HID_KEYBOARD_LED_EVENT == event_id && statusBar)
    {
        arduino_usb_hid_keyboard_event_data_t const * const leds = reinterpret_cast<arduino_usb_hid_keyboard_event_data_t const *>(event_data);
        leds_ = *leds;
    }
}

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
  sdCard = new SDCard();
  loadDirectoryContent();
  UI::Rect fullScreen = UI::Application::getFullFrameRect();
  application = new UI::Application();
  statusBar = new Statusbar(0,application);
  vmenu = new UI::VerticalMenu(menuItems,
                               UI::Rect(0,1,fullScreen.width, fullScreen.height - 1),
                               0,
                               application);
  btn.attachClick([]{vmenu->selectNext();});

  keyBoard.onEvent(ARDUINO_USB_HID_KEYBOARD_LED_EVENT, myEventHandler);
  
  keyBoard.begin();
  hwcdc.begin();
  usbcdc.begin(); 

  USB.productName("PassKey");
  USB.manufacturerName("Falk Software");
  USB.serialNumber("1");
  USB.firmwareVersion(1);
  USB.VID(0x413C); //Claim we are from DELL :P
  USB.PID(0x2010); //A nice generic Keyboard

  USB.begin();
}

unsigned count = 0;
void loop() {
  btn.tick();

  statusBar->setCapsLockStatus(leds_.capslock != 0);
  statusBar->setNumLockStatus(leds_.numlock != 0);
  statusBar->setScrollLockStatus(leds_.scrolllock != 0);


  application->update();

  delay(5);  
}
