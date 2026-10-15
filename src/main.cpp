#include "lib/SparkKeyboard/main.h"
#include "infra/HID/CONNECTION/main.h"
#include "shared/utils/blink-alert/main.h"
#include <Arduino.h>

// Hello World!
void mainSetup() {
    SparkKeyboard.sendKeyStroke(0);

    // Blinks for 3 secs
    blinkAlert(3);
    SparkKeyboard.println("# Olá, Mundo!!");
    SparkKeyboard.println("# Hello, World!!");
}

void mainLoop() {
    disconnectDevice();
    for (;;) {
        usbPoll();
        _delay_ms(5);
    }
};
