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
#include <stddef.h>
#include <stdint.h>

class SparktypeKeyboard : public DigiKeyboardDevice {
  public:
    size_t write(uint8_t chr);
    void sendKeyReport(unsigned char *array, const unsigned int size);
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
