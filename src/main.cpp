#include <Arduino.h>
#include "lib/DigiKeyboardPtBr.h"
#include "shared/utils/blink-alert/main.h"
#include "infra/OS/main.h"

void mainSetup() {
    DigiKeyboardPtBr.sendKeyStroke(0);

    // Blinks for 5 secs
    blinkAlert(5);
    _OS_ENUM os = detectOS();
    
}

void mainLoop() {
    return;
    
};
