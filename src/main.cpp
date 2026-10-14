#include "lib/SparkKeyboard/layouts/pt-br/main.h"
#include "infra/OS/main.h"
#include "shared/utils/blink-alert/main.h"
#include <Arduino.h>

// Hello World!
void mainSetup() {
    SparktypeKeyboardPTBR.sendKeyStroke(0);

    // Blinks for 3 secs
    blinkAlert(3);
    SparktypeKeyboardPTBR.println(
        "# Helo World! I'm hoWo and this is SparkType!");
}

void mainLoop() { return; };
