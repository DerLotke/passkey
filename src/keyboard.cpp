#include "keyboard.hpp"

#include <USBHID.h>
#include <Arduino.h>

ESP_EVENT_DEFINE_BASE(KEYBOARD_EVENT);

/*There is no header file ... we just have to forward declare it our self :( */
esp_err_t arduino_usb_event_handler_register_with(esp_event_base_t event_base, int32_t event_id, esp_event_handler_t event_handler, void *event_handler_arg);

void UsbKeyboard::usbKeyboardEventHandler( void* event_handler_arg, esp_event_base_t event_base,  int32_t event_id, void* event_data)
{
    if(event_handler_arg)
    {
        if (ARDUINO_USB_HID_KEYBOARD_EVENTS == event_base  && 
            ARDUINO_USB_HID_KEYBOARD_LED_EVENT == event_id)
        {
            UsbKeyboard *self = reinterpret_cast<UsbKeyboard*>(event_handler_arg);
            arduino_usb_hid_keyboard_event_data_t const * const leds = reinterpret_cast<arduino_usb_hid_keyboard_event_data_t const *>(event_data);
            self->onLedStateChange(*leds);
            self->leds_ = *leds;
        }
    }
}

UsbKeyboard::UsbKeyboard()
{
    
    arduino_usb_event_handler_register_with(ARDUINO_USB_HID_KEYBOARD_EVENTS, 
                                            ARDUINO_USB_HID_KEYBOARD_LED_EVENT, 
                                            UsbKeyboard::usbKeyboardEventHandler, 
                                            this);
    keyBoard_.begin();

    USB.productName("PassKey");
    USB.manufacturerName("Falk Software");
    USB.serialNumber("1");
    USB.firmwareVersion(1);
    USB.VID(0x413C); //Claim we are from DELL :P
    USB.PID(0x2010); //A nice generic Keyboard

    USB.begin();                            
}

void UsbKeyboard::onLedStateChange(arduino_usb_hid_keyboard_event_data_t const led)
{
    leds_ = led;

    EventData tmp;
    tmp.self = this;

    esp_event_post(KEYBOARD_EVENT, LedsUpdated,&tmp, sizeof(EventData),0);
}
