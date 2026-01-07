#include "main.h"
#include <DigiKeyboard.h>
#include <stdint.h>
#include <avr/interrupt.h>

LedsState getLedsState() {
    LedsState s;

    const uint8_t leds = g_keyboardLeds;

    s.caps = (leds & (1 << 1)) != 0;
    s.num  = (leds & (1 << 0)) != 0;
    s.scrl = (leds & (1 << 2)) != 0;

    s.replyReceived = g_ledReplyReceived;
    s.replyCount    = g_hostConfigRequestCount;

    return s;

}

void ensureCaps(bool expected);
void ensureNum(bool expected);
void ensureScrl(bool expected);

void resetLedsState(LedsState original) {
    ensureCaps(original.caps);
    ensureNum(original.num);
    ensureScrl(original.scrl);
    
}

void ensureCaps(bool expected) {
    for (uint8_t i = 0; i < 3; i++) {
        if (getLedsState().caps == expected) {
            return;
            
        }
        
        DigiKeyboard.sendKeyStroke(KEY_CAPS_LOCK);
        DigiKeyboard.delay(50);
    
    }
    
}

void ensureNum(bool expected) {
    for (uint8_t i = 0; i < 3; i++) {
        if (getLedsState().num == expected) {
            return;
            
        }
        
        DigiKeyboard.sendKeyStroke(KEY_NUM_LOCK);
        DigiKeyboard.delay(50);
    
    }
    
}

void ensureScrl(bool expected) {
    for (uint8_t i = 0; i < 3; i++) {
        if (getLedsState().scrl == expected) {
            return;
            
        }
        
        DigiKeyboard.sendKeyStroke(KEY_SCROLL_LOCK);
        DigiKeyboard.delay(50);
    
    }
    
}

void clearLedResponseState() {
    cli();
    g_ledReplyCount = 0;
    g_ledReplyReceived = false;
    sei();
    
};