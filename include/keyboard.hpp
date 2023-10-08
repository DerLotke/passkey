#pragma once

#include <USB.h>
#include <USBHIDKeyboard.h>
#include <esp_event.h>
#include <OneButton.h>

ESP_EVENT_DECLARE_BASE(KEYBOARD_EVENT);

class UsbKeyboard
{
    public:
        enum Events{
            KeyUp,
            KeyDown,
            KeySelect,
            LedsUpdated
        };

        struct EventData {
            UsbKeyboard *self;
        };

        UsbKeyboard(bool const skipUsb = false);
        ~UsbKeyboard();

        bool isCapsLockSet() const { return leds_.capslock != 0; }
        bool isNumLockSet() const { return leds_.numlock != 0; }
        bool isScrollLockSet() const { return leds_.scrolllock != 0; }

        void tick() { button_.tick(); }

    private:
        USBHIDKeyboard keyBoard_;
        arduino_usb_hid_keyboard_event_data_t leds_;
        OneButton button_;
        bool isFirstUpdate_; 

        void onLedStateChange(arduino_usb_hid_keyboard_event_data_t const);
        
        static void usbKeyboardEventHandler( void* event_handler_arg, esp_event_base_t event_base,  int32_t event_id, void* event_data);

};

