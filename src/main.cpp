#include <Arduino.h>
#include "lib/DigiKeyboardPtBr.h"
#include "shared/utils/blink-alert/main.h"
#include "infra/OS/main.h"
// #include "infra/TTY/main.h"

void mainSetup() {
    DigiKeyboardPtBr.sendKeyStroke(0);

    // Blinks for 5 secs
    blinkAlert(5);
    
    _OS_ENUM os = detectOS();
    
    if (os == Linux) {
        // Open terminal (bind, may change)
        DigiKeyboardPtBr.sendKeyStroke(KEY_T, MOD_GUI_LEFT);
        DigiKeyboardPtBr.delay(1250);
        
        // Open plaintext editor (may change too, in my system i'm using nano for fast edits in plain files)
        DigiKeyboardPtBr.print("nano");
        DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
        DigiKeyboardPtBr.delay(1250);
        
        // Write OS name
        DigiKeyboardPtBr.println("Linux!");
        
    } else if (os == Windows) {
        // Open run app
        DigiKeyboardPtBr.sendKeyStroke(KEY_D, MOD_GUI_LEFT);
        DigiKeyboardPtBr.delay(500);
        DigiKeyboardPtBr.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
        DigiKeyboardPtBr.delay(500);
        
        // Open notepad.exe
        DigiKeyboardPtBr.print("notepad.exe");
        DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
        DigiKeyboardPtBr.delay(500);
        
        // Write O name
        DigiKeyboardPtBr.println("Windows!");
        
    } else if (os == MacOS) {
        DigiKeyboardPtBr.println("MacOS!");
    
    }
    
}

void mainLoop() {
    return;
    
};
