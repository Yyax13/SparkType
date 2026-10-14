#include "lib/SparkKeyboard/main.h"
#include "shared/utils/blink-alert/main.h"
#include <Arduino.h>

// Hello World!
void mainSetup() {
    SparkKeyboard.sendKeyStroke(0);

    // Blinks for 3 secs
    blinkAlert(3);
    SparkKeyboard.println("# Helo World! I'm hoWo and this is SparkType!");
}

void mainLoop() { return; };
