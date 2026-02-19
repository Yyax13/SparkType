#include <Arduino.h>
#include "lib/SparkKeyboard/layouts/pt-br/main.h"
#include "shared/utils/blink-alert/main.h"

void mainSetup() {
    SparktypeKeyboardPTBR.sendKeyStroke(0);

    // Blinks for 5 secs
    blinkAlert(5);
    SparktypeKeyboardPTBR.println("Helo World!");
    
}

void mainLoop() {
    return;
    
};
