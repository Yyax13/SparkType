#include <Arduino.h>
#include "lib/DigiKeyboardPtBr.h"
#include "shared/utils/blink-alert/main.h"
#include "infra/OS/main.h"
// #include "infra/TTY/main.h"

void mainSetup() {
    DigiKeyboardPtBr.sendKeyStroke(0);

    // Blinks for 5 secs
    blinkAlert(5);
    
    // _OS_ENUM os = detectOS();
    
    // if (os == Linux) {
    //     DigiKeyboardPtBr.println("Linux!");
        
    // } else if (os == Windows) {
    //     DigiKeyboardPtBr.println("Windows!");
        
    // } else if (os == MacOS) {
    //     DigiKeyboardPtBr.println("MacOS!");
    
    // }
    
    DigiKeyboardPtBr.print("ptbr abcçABC123!@/");
    DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
    DigiKeyboardPtBr.sendKeyStroke(0x1e, 0x02 | 0xE000);
    DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
    
}

