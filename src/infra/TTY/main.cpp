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
            DigiKeyboardPtBr.print("yyax");
            DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
            DigiKeyboardPtBr.delay(1000);
            DigiKeyboardPtBr.print("yyax");
            DigiKeyboardPtBr.sendKeyStroke(KEY_ENTER);
            DigiKeyboardPtBr.delay(750);

        }

        static void CloseTTY() {
            DigiKeyboardPtBr.sendKeyStroke(KEY_F1, PTBR_MOD_CONTROL_LEFT | PTBR_MOD_ALT_LEFT);
            DigiKeyboardPtBr.delay(3500); 
        
        }

};