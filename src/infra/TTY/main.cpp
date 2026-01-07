/*
 * WARNING: UNSTABLE, USE BY YOUR OWN RISK
 * 
 * TODO:
 *      - Change the class def and implementation, incorrect implementation here, .cpp should not declare a class
 *      - Add authentication variables to TTY class
 */

#include "./../../lib/DigiKeyboardPtBr.h"

class TTY {
    public:
        /// FuncToRunInTTY must write anything into tty
        void runInTTY(void (*FuncToRunInTTY)(TTY&)) {
            TTY::OpenTTY();
            FuncToRunInTTY(*this);
            TTY::CloseTTY();

        }

    private:
        static void OpenTTY() {
            DigiKeyboardPtBr.sendKeyStroke(KEY_F3, PTBR_MOD_CONTROL_LEFT | PTBR_MOD_ALT_LEFT);
            DigiKeyboardPtBr.delay(2500);
            DigiKeyboardPtBr.print("user");
            DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
            DigiKeyboardPtBr.delay(1000);
            DigiKeyboardPtBr.print("pass");
            DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
            DigiKeyboardPtBr.delay(750);

        }

        static void CloseTTY() {
            DigiKeyboardPtBr.sendKeyStroke(KEY_F1, PTBR_MOD_CONTROL_LEFT | PTBR_MOD_ALT_LEFT);
            DigiKeyboardPtBr.delay(3500); 
        
        }

};