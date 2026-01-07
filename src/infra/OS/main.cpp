#include <Arduino.h>
#include "main.h"
#include "../../shared/utils/get-leds/main.h"
#include "../../shared/utils/blink-alert/main.h"
#include "../../lib/DigiKeyboardPtBr.h"

#define SHORT_BLINK blinkMs(50, 2);
#define MEDIUM_BLINK blinkMs(50, 5);
#define LED_ON digitalWrite(1, HIGH);
#define LED_OFF digitalWrite(1, LOW);

#define HOST_RESPONSE_TIMEOUT 1000
#define WINDOWS_HOST_REQUEST_COUNT 2

_OS_ENUM detectOS() {
    LedsState initialState = getLedsState();
    clearLedResponseState();
    
    DigiKeyboard.sendKeyStroke(KEY_CAPS_LOCK);
    DigiKeyboard.delay(HOST_RESPONSE_TIMEOUT);
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
        if (current.replyCount > WINDOWS_HOST_REQUEST_COUNT) {
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