#include "main.h"
#include <Arduino.h>

void blinkAlert(int times) {
    for (int i = 0; i < times; i++) {
        LED_ON;
        delay(450);
        LED_OFF;
        delay(50);

        for (int ii = 0; ii < 10; ii++) {
            LED_ON;
            delay(50);
            LED_OFF;
            delay(50);
        }
    }
}

void blinkMs(int ms, int times) {
    if (ms < 50 || times < 1)
        return;

    for (int i = 0; i < times; i++) {
        LED_ON;
        delay(ms);
        LED_OFF;
    }
};
