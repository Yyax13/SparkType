#include <Arduino.h>
#include "main.h"

void blinkAlert(int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(1, HIGH);
        delay(450);
        digitalWrite(1, LOW);
        delay(50);
        
        for (int ii = 0; ii < 10; ii++) {
            digitalWrite(1, HIGH);
            delay(50);
            digitalWrite(1, LOW);
            delay(50);
            
        }
        
    }

}

void blinkMs(int ms, int times) {
    if (ms < 50 || times < 1) {
        return;
        
    }
    
    for (int i = 0; i < times; i++) {
        digitalWrite(1, HIGH);
        delay(ms);
        digitalWrite(1, LOW);
        
    }
    
};