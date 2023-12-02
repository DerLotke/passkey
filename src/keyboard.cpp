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

UsbKeyboard::UsbKeyboard(bool const skipUsb):
    button_(0, true ),
    isFirstUpdate_(true)
{
    
    arduino_usb_event_handler_register_with(ARDUINO_USB_HID_KEYBOARD_EVENTS, 
                                            ARDUINO_USB_HID_KEYBOARD_LED_EVENT, 
                                            UsbKeyboard::usbKeyboardEventHandler, 
                                            this);
    if(!skipUsb) {
        keyBoard_.begin();

        USB.productName("PassKey");
        USB.manufacturerName("Falk Software");
        USB.serialNumber("1");
        USB.firmwareVersion(1);
        USB.VID(0x413C); //Claim we are from DELL :P
        USB.PID(0x2010); //A nice generic Keyboard

        USB.begin();
    }
    
    button_.attachClick([]{esp_event_post(KEYBOARD_EVENT, KeyDown, nullptr, 0, 0); });
    button_.attachDuringLongPress([]{esp_event_post(KEYBOARD_EVENT, KeySelect, nullptr, 0, 0); });                            
}

void UsbKeyboard::onLedStateChange(arduino_usb_hid_keyboard_event_data_t const led)
{
    arduino_usb_hid_keyboard_event_data_t changed;
    
    changed.leds = led.leds ^ leds_.leds; //Determine changed leds by using XOR 
    leds_ = led;

    EventData tmp;
    tmp.self = this;

    esp_event_post(KEYBOARD_EVENT, LedsUpdated,&tmp, sizeof(EventData),0);

    if(!isFirstUpdate_)
    {
        if (changed.capslock) 
        {
            esp_event_post(KEYBOARD_EVENT, KeyDown,&tmp, sizeof(EventData),0);
        }

        if (changed.numlock) 
        {
            esp_event_post(KEYBOARD_EVENT, KeyUp,&tmp, sizeof(EventData),0);
        }

        if (changed.scrolllock) 
        {
            esp_event_post(KEYBOARD_EVENT, KeySelect,&tmp, sizeof(EventData),0);
        }
    }
    
    isFirstUpdate_ = false;
}

void UsbKeyboard::sendKeyStrokes(KeyStrokeFile &input)
{
    for(KeyStrokeFile::KeyStrokeData data = input.getNextCommand();
        data.type != KeyStrokeFile::CommandTypes::EndOfFile;
        data = input.getNextCommand())
        {
            switch (data.type)
            {
            case KeyStrokeFile::CommandTypes::KeyPress: keyBoard_.pressRaw(data.parameter); break;
            case KeyStrokeFile::CommandTypes::KeyRelease: keyBoard_.releaseRaw(data.parameter); break;
            case KeyStrokeFile::CommandTypes::TypeDelay: delayMicroseconds(data.parameter * 1000); break;
            
            default:
                break;
            }
        }
    keyBoard_.releaseAll();
}
