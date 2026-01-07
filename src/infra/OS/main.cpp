#include <Arduino.h>
#include <DigiKeyboard.h>
#include "main.h"
#include "../HID/LEDS/main.h"
#include "../../shared/utils/blink-alert/main.h"
#include "../HID/CONNECTION/main.h"

#define SHORT_BLINK blinkMs(50, 2);
#define MEDIUM_BLINK blinkMs(50, 5);
#define LED_ON digitalWrite(1, HIGH);
#define LED_OFF digitalWrite(1, LOW);

#define HOST_RESPONSE_TIMEOUT 2000
#define WINDOWS_HOST_REQUEST_COUNT 15

_OS_ENUM detectOS() {
    LedsState initialState = getLedsState();
    reconnectDevice();
    
    LedsState current = getLedsState();
    
    if (!current.caps) {
        LED_ON
        DigiKeyboard.sendKeyStroke(KEY_CAPS_LOCK);
        DigiKeyboard.delay(HOST_RESPONSE_TIMEOUT);
        LED_OFF
        SHORT_BLINK
        
    }
    
    _OS_ENUM os;
    if (current.replyReceived) {
        MEDIUM_BLINK
        if (g_hostConfigRequestCount > WINDOWS_HOST_REQUEST_COUNT) {
            os = Windows;
            
        } else {
            os = Linux;
            
        }
        
    } else {
        os = MacOS;
        
    }
    
    clearLedResponseState();
    resetLedsState(initialState);
    
    DigiKeyboard.delay(500);
    return os;
    
};