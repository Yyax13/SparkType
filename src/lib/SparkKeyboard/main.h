#ifndef DIGILAYOUTS_H
#define DIGILAYOUTS_H

/*
 * DOCS:
 *      Hello dev, let's learn how to use SparkKeyboard!! :)
 *      Just add your layout as a directory in layouts!
 *      Example with pt-br: 
 *          layouts/pt-br/main.h:
 *              The file must include this main.h (s/l/SparkKeyboard/main.h).
 *              Here, you need to define some macros (as seen in the doc file
 *              base-mods.txt).
 *              
 *              The file also need to extern something like:
 *              extern SparktypeKeyboard SparktypeKeyboardPTBR; 
 * 
 *          layouts/pt-br/main.cpp:
 *              The file must include his own main.h (l/pt-br/main.h) and
 *              define declarations for:
 *                - size_t SparktypeKeyboard::write
 *                - void SparktypeKeyboard::sendKeyReport
 *              
 *              We also recommend using the static _ascii_map preset in
 *              ascii-map.txt to avoid errors.
 *              And, is recommended to using #ifdef isntead of #pragma once
 *              to ensure that you will correctly use the layout :)
 * 
 *              The file also need to declare something like:
 *              SparktypeKeyboard SparktypeKeyboardPTBR = SparktypeKeyboard();
 *              
 *          After creating the layout, select it in src/config.h by defining
 *          its SPARKTYPE_LAYOUT_* macro, then include this main.h and use the
 *          generic "SparkKeyboard" handle! :)
 * 
 */

#include "../../config.h"

#include <DigiKeyboard.h>
#include <avr/pgmspace.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

class SparktypeKeyboard : public DigiKeyboardDevice {
  public:
    bool jitter = false;
    unsigned int msDelay = 0;
    size_t write(uint8_t chr);
    void sendKeyReport(unsigned char *array, const unsigned int size);

    // If msDelay != 0 delay the connection up to 110ms
    // If jitter = true, randomly spread the delay between 60 and 160 percent. Cap at 176ms
    void keyDelay() {
        if (msDelay == 0) {
            return;
        }

        unsigned int wait = msDelay % 111;

        if (jitter && msDelay > 5) {
            static uint32_t state = 0x9E3779B9UL;
            state = state * 1664525UL + 1013904223UL;

            unsigned int factor = 60 + (unsigned int)((state >> 16) % 101);
            wait = (wait * factor) / 100;

            if (wait > 176) {
                wait = 176;
            }
        }

        if (wait) {
            delay(wait);
        }
    }

    void sendKeyStroke(byte keyStroke) {
        keyDelay();
        DigiKeyboardDevice::sendKeyStroke(keyStroke);
    }

    void sendKeyStroke(byte keyStroke, byte modifiers) {
        keyDelay();
        DigiKeyboardDevice::sendKeyStroke(keyStroke, modifiers);
    }

    void sendKeyStroke(byte keyStroke, byte modifiers, bool aUseFeedbackLed) {
        keyDelay();
        DigiKeyboardDevice::sendKeyStroke(keyStroke, modifiers,
                                          aUseFeedbackLed);
    }
};

/*
 * Layout selection.
 * Pick exactly one layout in src/config.h, then use the generic
 * "SparkKeyboard" handle everywhere without caring about the locale.
 */
#if defined(SPARKTYPE_LAYOUT_PTBR)
#include "layouts/pt-br/main.h"
#define SparkKeyboard SparktypeKeyboardPTBR
#else
#error "No SparkType layout selected: define one layout in src/config.h."
#endif

#endif
