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

    // With delay 50ms without jitter
    SparkKeyboard.msDelay = 50;
    SparkKeyboard.println("# Hello, World!!");

    // With jitter
    SparkKeyboard.jitter = true;
    SparkKeyboard.println("# Bonjour le monde!!");

    // Higher delay
    SparkKeyboard.msDelay = 80;
    SparkKeyboard.println("# Ciao mondo!!");
}

void mainLoop() {
    shutdevice();
    for (;;)
        continue;
};
