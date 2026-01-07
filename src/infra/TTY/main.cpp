/*
 * TODO:
 *      
 */

#include "./../../lib/DigiKeyboardPtBr.h"
#include "main.h";

/// FuncToRunInTTY must write anything into tty
void TTY::runInTTY(void (*FuncToRunInTTY)(TTY&)) {
    TTY::OpenTTY();
    FuncToRunInTTY(*this);
    TTY::CloseTTY();

}

void TTY::OpenTTY() {
    DigiKeyboardPtBr.sendKeyStroke(KEY_F3, PTBR_MOD_CONTROL_LEFT | PTBR_MOD_ALT_LEFT);
    DigiKeyboardPtBr.delay(2500);
    DigiKeyboardPtBr.print(TTY::user);
    DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
    DigiKeyboardPtBr.delay(1000);
    DigiKeyboardPtBr.print(TTY::pass);
    DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
    DigiKeyboardPtBr.delay(750);

}

void TTY::CloseTTY() {
    DigiKeyboardPtBr.sendKeyStroke(KEY_F1, PTBR_MOD_CONTROL_LEFT | PTBR_MOD_ALT_LEFT);
    DigiKeyboardPtBr.delay(3500); 

}

TTY tty = TTY();