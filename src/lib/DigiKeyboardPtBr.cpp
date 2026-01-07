#include "DigiKeyboardPtBr.h"
#include <avr/pgmspace.h>
#include <stddef.h>
#include <stdint.h>



static const uint16_t _ascii_ptbr_map[128] PROGMEM = {
    0x00,             // NUL
    0x00,             // SOH
    0x00,             // STX
    0x00,             // ETX
    0x00,             // EOT
    0x00,             // ENQ
    0x00,             // ACK
    0x00,             // BEL
    0x2a,     // BS Backspace
    0x2b,     // TAB  Tab
    0x28,     // LF Enter
    0x00,             // VT
    0x00,             // FF
    0x00,             // CR
    0x00,             // SO
    0x00,             // SI
    0x00,             // DEL
    0x00,             // DC1
    0x00,             // DC2
    0x00,             // DC3
    0x00,             // DC4
    0x00,             // NAK
    0x00,             // SYN
    0x00,             // ETB
    0x00,             // CAN
    0x00,             // EM
    0x00,             // SUB
    0x00,             // ESC
    0x00,             // FS
    0x00,             // GS
    0x00,             // RS
    0x00,             // US
    0x2c,      //  ' '
    0x1e|PTBR_MOD_SHIFT_LEFT,    // !
    0x35|PTBR_MOD_SHIFT_LEFT, //0x1F|PTBR_MOD_SHIFT_LEFT,    // "
    0x20|PTBR_MOD_SHIFT_LEFT, //0x38,    // #
    0x21|PTBR_MOD_SHIFT_LEFT,    // $
    0x22|PTBR_MOD_SHIFT_LEFT,    // %
    0x24|PTBR_MOD_SHIFT_LEFT, //0x23|PTBR_MOD_SHIFT_LEFT,    // &
    0x35, //0x32|PTBR_MOD_SHIFT_LEFT,          // '
    0x26|PTBR_MOD_SHIFT_LEFT, //0x25|PTBR_MOD_SHIFT_LEFT,    // (
    0x27|PTBR_MOD_SHIFT_LEFT, //0x26|PTBR_MOD_SHIFT_LEFT,    // )
    0x25|PTBR_MOD_SHIFT_LEFT, //0x30|PTBR_MOD_SHIFT_LEFT,    // *
    0x2E|PTBR_MOD_SHIFT_LEFT, //0x30,    // +
    0x36,          // ,
    0x2D, //0x38,          // -
    0x37,          // .
    0x14|PTBR_MOD_ALT_RIGHT, //0x24|PTBR_MOD_SHIFT_LEFT,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x38|PTBR_MOD_SHIFT_LEFT, //0x37|PTBR_MOD_SHIFT_LEFT,      // :
    0x38, //0x36|PTBR_MOD_SHIFT_LEFT,          // ;
    0x36|PTBR_MOD_SHIFT_LEFT, //0x64,      // <
    0x2E, //0x27|PTBR_MOD_SHIFT_LEFT,          // =
    0x37|PTBR_MOD_SHIFT_LEFT, //0x64|PTBR_MOD_SHIFT_LEFT,      // >
    KEY_W|PTBR_MOD_ALT_RIGHT, //0x2D|PTBR_MOD_SHIFT_LEFT,      // ?
    0x1f|PTBR_MOD_SHIFT_LEFT, //0x14|PTBR_MOD_ALT_RIGHT,      // @
    0x04|PTBR_MOD_SHIFT_LEFT,      // A
    0x05|PTBR_MOD_SHIFT_LEFT,      // B
    0x06|PTBR_MOD_SHIFT_LEFT,      // C
    0x07|PTBR_MOD_SHIFT_LEFT,      // D
    0x08|PTBR_MOD_SHIFT_LEFT,      // E
    0x09|PTBR_MOD_SHIFT_LEFT,      // F
    0x0a|PTBR_MOD_SHIFT_LEFT,      // G
    0x0b|PTBR_MOD_SHIFT_LEFT,      // H
    0x0c|PTBR_MOD_SHIFT_LEFT,      // I
    0x0d|PTBR_MOD_SHIFT_LEFT,      // J
    0x0e|PTBR_MOD_SHIFT_LEFT,      // K
    0x0f|PTBR_MOD_SHIFT_LEFT,      // L
    0x10|PTBR_MOD_SHIFT_LEFT,      // M
    0x11|PTBR_MOD_SHIFT_LEFT,      // N
    0x12|PTBR_MOD_SHIFT_LEFT,      // O
    0x13|PTBR_MOD_SHIFT_LEFT,      // P
    0x14|PTBR_MOD_SHIFT_LEFT,      // Q
    0x15|PTBR_MOD_SHIFT_LEFT,      // R
    0x16|PTBR_MOD_SHIFT_LEFT,      // S
    0x17|PTBR_MOD_SHIFT_LEFT,      // T
    0x18|PTBR_MOD_SHIFT_LEFT,      // U
    0x19|PTBR_MOD_SHIFT_LEFT,      // V
    0x1a|PTBR_MOD_SHIFT_LEFT,      // W
    0x1b|PTBR_MOD_SHIFT_LEFT,      // X
    0x1c|PTBR_MOD_SHIFT_LEFT, //0x1d|PTBR_MOD_SHIFT_LEFT,      // Y
    0x1d|PTBR_MOD_SHIFT_LEFT, //0x1c|PTBR_MOD_SHIFT_LEFT,      // Z
    0x30, //0x25|PTBR_MOD_ALT_RIGHT,          // [
    0x64, //0x2d|PTBR_MOD_ALT_RIGHT,          // bslash
    0x32, //0x26|PTBR_MOD_ALT_RIGHT,          // ]
    0x35,    // ^
    0x2D|PTBR_MOD_SHIFT_LEFT, //0x38|PTBR_MOD_SHIFT_LEFT,    // _
    0x2E|PTBR_MOD_SHIFT_LEFT,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c, //0x1d,          // y
    0x1d, //0x1c,          // z
    0x30|PTBR_MOD_SHIFT_LEFT, //0x24|PTBR_MOD_ALT_RIGHT,    // {
    0x64|PTBR_MOD_SHIFT_LEFT,    // |
    0x32|PTBR_MOD_SHIFT_LEFT, //0x27|PTBR_MOD_ALT_RIGHT,    // }
    0x64, //0x30|PTBR_MOD_ALT_RIGHT,    // ~
    0       // DEL
};

size_t DigiKeyboardDevicePtBr::write(uint8_t chr) {

        //çÇ
        if (chr == 195) {
          sendKeyStroke(0x33); 
          //sendKeyStroke(0x33, MOD_SHIFT_LEFT);
        }
        else {          
          unsigned int temp = pgm_read_word_near(_ascii_ptbr_map + chr);          
          unsigned char low = temp & 0xFF;
          unsigned char high = (temp >> 8) & 0xFF;
          sendKeyStroke(low,high);
        }
        
        return 1;
    }

// size_t DigiKeyboardDevicePtBr::write(uint8_t chr) {
//     static bool utf8 = false;

//     if (chr == 0xC3) {
//         utf8 = true;
//         return 0;
//     }

//     if (utf8) {
//         utf8 = false;

//         if (chr == 0xA7) { // ç
//             sendKeyStroke(0x33);
//             return 1;
//         }

//         if (chr == 0x87) { // Ç
//             sendKeyStroke(0x33, PTBR_MOD_SHIFT_LEFT);
//             return 1;
//         }

//         return 0;
//     }

//     unsigned int temp = pgm_read_word_near(_ascii_ptbr_map + chr);
//     unsigned char low = temp & 0xFF;
//     unsigned char high = (temp >> 8) & 0xFF;
//     sendKeyStroke(low, high);

//     return 1;
// }

void DigiKeyboardDevicePtBr::sendKeyReport(unsigned char *array, const unsigned int size) {
    while (!usbInterruptIsReady()) {
        // Note: We wait until we can send keyPress
        //       so we know the previous keyPress was
        //       sent.
        usbPoll();
        _delay_ms(5);
    }

    usbSetInterrupt(array, size);
}

DigiKeyboardDevicePtBr DigiKeyboardPtBr = DigiKeyboardDevicePtBr();