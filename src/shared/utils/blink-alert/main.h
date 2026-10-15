#pragma once

#include <Arduino.h>

#define LED_ON digitalWrite(1, HIGH);
#define LED_OFF digitalWrite(1, LOW);

/// Receive `int times`, every time takes a second to run
void blinkAlert(int times);

/// Min ms: 50;
/// Min times: 1;
void blinkMs(int ms, int times);

#define SHORT_BLINK blinkMs(50, 2);
#define MEDIUM_BLINK blinkMs(50, 5);
