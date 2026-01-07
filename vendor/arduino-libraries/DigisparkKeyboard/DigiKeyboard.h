/*
 * Based on Obdev's AVRUSB code and under the same license.
 *
 * TODO: Make a proper file header. :-)
 * Modified for Digispark by Digistump
 * 
 * Modified by Yyax13 to avoid multiple defs error
 */
#ifndef __DigiKeyboard_h__
#define __DigiKeyboard_h__

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "usbdrv.h"
#include "keylayouts.h"

typedef uint8_t byte;

#define TEST_STRING "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

#define BUFFER_SIZE 2 // Minimum of 2: 1 for modifiers + 1 for keystroke

#ifndef USBRQ_SET_IDLE
#define USBRQ_SET_IDLE 0x0A
#endif

#define MOD_CONTROL_LEFT    MODIFIERKEY_LEFT_CTRL
#define MOD_SHIFT_LEFT      MODIFIERKEY_LEFT_SHIFT
#define MOD_ALT_LEFT        MODIFIERKEY_LEFT_ALT
#define MOD_GUI_LEFT        MODIFIERKEY_LEFT_GUI
#define MOD_CONTROL_RIGHT   MODIFIERKEY_RIGHT_CTRL
#define MOD_SHIFT_RIGHT     MODIFIERKEY_RIGHT_SHIFT
#define MOD_ALT_RIGHT       MODIFIERKEY_RIGHT_ALT
#define MOD_GUI_RIGHT       MODIFIERKEY_RIGHT_GUI

class DigiKeyboardDevice: public Print {
public:
    DigiKeyboardDevice() {
        noInterrupts();
        usbDeviceDisconnect();
        _delay_ms(250);
        usbDeviceConnect();

        usbInit();

        interrupts();

        // TODO: Remove the next two lines once we fix
        //       missing first keystroke bug properly.
        memset(reportBuffer, 0, sizeof(reportBuffer));
        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }

    void update() {
        usbPoll();
    }

    // delay while updating until we are finished delaying
    void delay(long milli) {
        unsigned long last = millis();
        while (milli > 0) {
            unsigned long now = millis();
            milli -= now - last;
            last = now;
            update();
        }
    }

    //sendKeyStroke: sends a key press AND release
    void sendKeyStroke(byte keyStroke) {
        sendKeyStroke(keyStroke, 0);
    }

    void enableLEDFeedback() {
        sUseFeedbackLed = true;
        pinMode(LED_BUILTIN, OUTPUT);
    }

    void disableLEDFeedback() {
        sUseFeedbackLed = false;
    }

    //sendKeyStroke: sends a key press AND release with modifiers
    void sendKeyStroke(byte keyStroke, byte modifiers) {
        sendKeyStroke(keyStroke, modifiers, false);
    }

    //sendKeyStroke: sends a key press AND release with modifiers
    void sendKeyStroke(byte keyStroke, byte modifiers, bool aUseFeedbackLed) {
        if (aUseFeedbackLed) {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        sendKeyPress(keyStroke, modifiers);
        // This stops endlessly repeating keystrokes:
        sendKeyPress(0, 0); // send key release
        if (aUseFeedbackLed) {
            digitalWrite(LED_BUILTIN, LOW);
        }
    }

    //sendKeyPress: sends a key press only - no release
    //to release the key, send again with keyPress=0
    void sendKeyPress(byte keyPress) {
        sendKeyPress(keyPress, 0);
    }

    //sendKeyPress: sends a key press only, with modifiers - no release
    //to release the key, send again with keyPress=0
    void sendKeyPress(byte keyPress, byte modifiers) {
        while (!usbInterruptIsReady()) {
            // Note: We wait until we can send keyPress
            //       so we know the previous keyPress was
            //       sent.
            usbPoll();
            _delay_ms(5);
        }

        memset(reportBuffer, 0, sizeof(reportBuffer));

        reportBuffer[0] = modifiers;
        reportBuffer[1] = keyPress;

        usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    }

    uint8_t keycode_to_modifier(uint8_t keycode) {
        uint8_t modifier = 0;

#ifdef SHIFT_MASK
        if (keycode & SHIFT_MASK)
            modifier |= MODIFIERKEY_SHIFT;
#endif
#ifdef ALTGR_MASK
        if (keycode & ALTGR_MASK)
            modifier |= MODIFIERKEY_RIGHT_ALT;
#endif
#ifdef RCTRL_MASK
        if (keycode & RCTRL_MASK) modifier |= MODIFIERKEY_RIGHT_CTRL;
#endif
        return modifier;
    }

    /*
     * Mask keycodes to ascii subset (+ a few F keys)
     */
    uint8_t keycode_to_key(uint8_t keycode) {
        uint8_t key = keycode & KEYCODE_MASK_SCANCODE;
        // the only valid ASCII code which has a scancode > 63
        if (key == KEY_NON_US_BS_MAPPING) {
            key = (uint8_t) KEY_NON_US_BS;
        }
        return key;
    }

    /*
     * Convert ASCII to USB code
     */
    size_t write(uint8_t chr) {
        uint8_t data = 0;
        if (chr == '\b') {
            data = (uint8_t) KEY_BACKSPACE; // 0x08
        } else if (chr == '\t') {
            data = (uint8_t) KEY_TAB;       // 0x09
        } else if (chr == '\n') {
            data = (uint8_t) KEY_ENTER;     // 0x0A
        } else if (chr == '\r') {
            data = (uint8_t) KEY_ENTER;     // 0x0D
        } else if (chr >= 0x20) {
            // read from mapping table
            data = pgm_read_byte_near(keycodes_ascii + (chr - 0x20));
        }
        if (data) {
            sendKeyStroke(keycode_to_key(data), keycode_to_modifier(data), sUseFeedbackLed);
        }
        return 1;
    }

    bool sUseFeedbackLed = false;
    uchar reportBuffer[2];    // buffer for HID reports [ 1 modifier byte + (len-1) key strokes]
    using Print::write;
};

extern DigiKeyboardDevice DigiKeyboard;

extern const PROGMEM uchar usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH];
extern volatile uchar g_keyboardLeds;
extern volatile bool g_ledReplyReceived;
extern volatile uint16_t g_ledReplyCount;

#ifdef __cplusplus
extern "C" {
#endif

uchar usbFunctionSetup(uchar data[8]);

#ifdef __cplusplus
}
#endif

#endif // __DigiKeyboard_h__
