#include "main.h"

/*
 * Brazilian ABNT2 layout.
 *
 * The device only emits USB HID usages. The host OS, configured with the
 * ABNT2 layout, turns those usages into characters. Accented letters are
 * produced through the ABNT2 dead keys:
 *
 *   dead acute      HID 0x2F               (physical "[ {" key)  -> a e i o u y
 *   dead grave      HID 0x2F + Shift                             -> a e i o u
 *   dead tilde      HID 0x34               (physical "' \"" key) -> a e i o u n
 *   dead circumflex HID 0x34 + Shift                             -> a e i o u
 *   dead diaeresis  HID 0x23 + Shift       (Shift+6)             -> a e i o u y
 *   cedilla         HID 0x33               (physical "; :" key)  -> c
 *
 * Every stroke is packed as (HID usage | (modifier << 8)), the same packing
 * used by _ascii_map: low byte = keycode, high byte = modifier bitmap.
 *
 * dev note: took me 4 hours to find the layout online and port it here :p
 */

#define PTBR_DEAD_ACUTE (0x2F)
#define PTBR_DEAD_GRAVE (0x2F | PTBR_MOD_SHIFT_LEFT)
#define PTBR_DEAD_TILDE (0x34)
#define PTBR_DEAD_CIRCUMFLEX (0x34 | PTBR_MOD_SHIFT_LEFT)
#define PTBR_DEAD_DIAERESIS (0x23 | PTBR_MOD_SHIFT_LEFT)
#define PTBR_CEDILLA (0x33)

#define PTBR_KEY_A (0x04)
#define PTBR_KEY_C (0x06)
#define PTBR_KEY_E (0x08)
#define PTBR_KEY_I (0x0C)
#define PTBR_KEY_N (0x11)
#define PTBR_KEY_O (0x12)
#define PTBR_KEY_U (0x18)
#define PTBR_KEY_Y (0x1C)
#define PTBR_KEY_SPACE (0x2C)

static const uint16_t _ascii_map[128] PROGMEM = {
    0x00,                       // NUL
    0x00,                       // SOH
    0x00,                       // STX
    0x00,                       // ETX
    0x00,                       // EOT
    0x00,                       // ENQ
    0x00,                       // ACK
    0x00,                       // BEL
    0x2a,                       // BS Backspace
    0x2b,                       // TAB  Tab
    0x28,                       // LF Enter
    0x00,                       // VT
    0x00,                       // FF
    0x00,                       // CR
    0x00,                       // SO
    0x00,                       // SI
    0x00,                       // DEL
    0x00,                       // DC1
    0x00,                       // DC2
    0x00,                       // DC3
    0x00,                       // DC4
    0x00,                       // NAK
    0x00,                       // SYN
    0x00,                       // ETB
    0x00,                       // CAN
    0x00,                       // EM
    0x00,                       // SUB
    0x00,                       // ESC
    0x00,                       // FS
    0x00,                       // GS
    0x00,                       // RS
    0x00,                       // US
    0x2c,                       //  ' '
    0x1e | PTBR_MOD_SHIFT_LEFT, // !
    0x35 | PTBR_MOD_SHIFT_LEFT, // "
    0x20 | PTBR_MOD_SHIFT_LEFT, // #
    0x21 | PTBR_MOD_SHIFT_LEFT, // $
    0x22 | PTBR_MOD_SHIFT_LEFT, // %
    0x24 | PTBR_MOD_SHIFT_LEFT, // &
    0x35,                       // '
    0x26 | PTBR_MOD_SHIFT_LEFT, // (
    0x27 | PTBR_MOD_SHIFT_LEFT, // )
    0x25 | PTBR_MOD_SHIFT_LEFT, // *
    0x2E | PTBR_MOD_SHIFT_LEFT, // +
    0x36,                       // ,
    0x2D,                       // -
    0x37,                       // .
    0x14 | PTBR_MOD_ALT_RIGHT,  // /  (AltGr+Q on ABNT2)
    0x27,                       // 0
    0x1e,                       // 1
    0x1f,                       // 2
    0x20,                       // 3
    0x21,                       // 4
    0x22,                       // 5
    0x23,                       // 6
    0x24,                       // 7
    0x25,                       // 8
    0x26,                       // 9
    0x38 | PTBR_MOD_SHIFT_LEFT, // :
    0x38,                       // ;
    0x36 | PTBR_MOD_SHIFT_LEFT, // <
    0x2E,                       // =
    0x37 | PTBR_MOD_SHIFT_LEFT, // >
    0x1a | PTBR_MOD_ALT_RIGHT,  // ?  (AltGr+W on ABNT2)
    0x1f | PTBR_MOD_SHIFT_LEFT, // @
    0x04 | PTBR_MOD_SHIFT_LEFT, // A
    0x05 | PTBR_MOD_SHIFT_LEFT, // B
    0x06 | PTBR_MOD_SHIFT_LEFT, // C
    0x07 | PTBR_MOD_SHIFT_LEFT, // D
    0x08 | PTBR_MOD_SHIFT_LEFT, // E
    0x09 | PTBR_MOD_SHIFT_LEFT, // F
    0x0a | PTBR_MOD_SHIFT_LEFT, // G
    0x0b | PTBR_MOD_SHIFT_LEFT, // H
    0x0c | PTBR_MOD_SHIFT_LEFT, // I
    0x0d | PTBR_MOD_SHIFT_LEFT, // J
    0x0e | PTBR_MOD_SHIFT_LEFT, // K
    0x0f | PTBR_MOD_SHIFT_LEFT, // L
    0x10 | PTBR_MOD_SHIFT_LEFT, // M
    0x11 | PTBR_MOD_SHIFT_LEFT, // N
    0x12 | PTBR_MOD_SHIFT_LEFT, // O
    0x13 | PTBR_MOD_SHIFT_LEFT, // P
    0x14 | PTBR_MOD_SHIFT_LEFT, // Q
    0x15 | PTBR_MOD_SHIFT_LEFT, // R
    0x16 | PTBR_MOD_SHIFT_LEFT, // S
    0x17 | PTBR_MOD_SHIFT_LEFT, // T
    0x18 | PTBR_MOD_SHIFT_LEFT, // U
    0x19 | PTBR_MOD_SHIFT_LEFT, // V
    0x1a | PTBR_MOD_SHIFT_LEFT, // W
    0x1b | PTBR_MOD_SHIFT_LEFT, // X
    0x1c | PTBR_MOD_SHIFT_LEFT, // Y
    0x1d | PTBR_MOD_SHIFT_LEFT, // Z
    0x30,                       // [  (physical "] }" key on ABNT2)
    0x64,                       // bslash (physical <LSGT> key)
    0x31,                       // ]  (physical "\ |" key on ABNT2)
    0x34 | PTBR_MOD_ALT_RIGHT |
        PTBR_MOD_SHIFT_LEFT,    // ^  (AltGr+Shift+tilde key)
    0x2D | PTBR_MOD_SHIFT_LEFT, // _
    0x2F | PTBR_MOD_ALT_RIGHT |
        PTBR_MOD_SHIFT_LEFT,    // `  (AltGr+Shift+acute key)
    0x04,                       // a
    0x05,                       // b
    0x06,                       // c
    0x07,                       // d
    0x08,                       // e
    0x09,                       // f
    0x0a,                       // g
    0x0b,                       // h
    0x0c,                       // i
    0x0d,                       // j
    0x0e,                       // k
    0x0f,                       // l
    0x10,                       // m
    0x11,                       // n
    0x12,                       // o
    0x13,                       // p
    0x14,                       // q
    0x15,                       // r
    0x16,                       // s
    0x17,                       // t
    0x18,                       // u
    0x19,                       // v
    0x1a,                       // w
    0x1b,                       // x
    0x1c,                       // y
    0x1d,                       // z
    0x30 | PTBR_MOD_SHIFT_LEFT, // {  (physical "] }" key + Shift)
    0x64 | PTBR_MOD_SHIFT_LEFT, // |
    0x31 | PTBR_MOD_SHIFT_LEFT, // }  (physical "\ |" key + Shift)
    0x34 | PTBR_MOD_ALT_RIGHT,  // ~  (AltGr+tilde key)
    0                           // DEL

};

/*
 * Codepoint -> ABNT2 strokes.
 *   stroke1 : dead key (or a direct key when stroke2 == 0)
 *   stroke2 : base letter, 0 when the character is typed with a single stroke
 */
struct PTBRAccentMap {
    uint16_t codepoint;
    uint16_t stroke1;
    uint16_t stroke2;
};

static const PTBRAccentMap _accent_map[] PROGMEM = {
    // a
    {0x00E0, PTBR_DEAD_GRAVE, PTBR_KEY_A},      // à
    {0x00E1, PTBR_DEAD_ACUTE, PTBR_KEY_A},      // á
    {0x00E2, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_A}, // â
    {0x00E3, PTBR_DEAD_TILDE, PTBR_KEY_A},      // ã
    {0x00E4, PTBR_DEAD_DIAERESIS, PTBR_KEY_A},  // ä
    // c
    {0x00E7, PTBR_CEDILLA, 0}, // ç
    // e
    {0x00E8, PTBR_DEAD_GRAVE, PTBR_KEY_E},      // è
    {0x00E9, PTBR_DEAD_ACUTE, PTBR_KEY_E},      // é
    {0x00EA, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_E}, // ê
    {0x00EB, PTBR_DEAD_DIAERESIS, PTBR_KEY_E},  // ë
    // i
    {0x00EC, PTBR_DEAD_GRAVE, PTBR_KEY_I},      // ì
    {0x00ED, PTBR_DEAD_ACUTE, PTBR_KEY_I},      // í
    {0x00EE, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_I}, // î
    {0x00EF, PTBR_DEAD_DIAERESIS, PTBR_KEY_I},  // ï
    // n
    {0x00F1, PTBR_DEAD_TILDE, PTBR_KEY_N}, // ñ
    // o
    {0x00F2, PTBR_DEAD_GRAVE, PTBR_KEY_O},      // ò
    {0x00F3, PTBR_DEAD_ACUTE, PTBR_KEY_O},      // ó
    {0x00F4, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_O}, // ô
    {0x00F5, PTBR_DEAD_TILDE, PTBR_KEY_O},      // õ
    {0x00F6, PTBR_DEAD_DIAERESIS, PTBR_KEY_O},  // ö
    // u
    {0x00F9, PTBR_DEAD_GRAVE, PTBR_KEY_U},      // ù
    {0x00FA, PTBR_DEAD_ACUTE, PTBR_KEY_U},      // ú
    {0x00FB, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_U}, // û
    {0x00FC, PTBR_DEAD_DIAERESIS, PTBR_KEY_U},  // ü
    // y
    {0x00FD, PTBR_DEAD_ACUTE, PTBR_KEY_Y},     // ý
    {0x00FF, PTBR_DEAD_DIAERESIS, PTBR_KEY_Y}, // ÿ
    // uppercase a
    {0x00C0, PTBR_DEAD_GRAVE, PTBR_KEY_A | PTBR_MOD_SHIFT_LEFT},      // À
    {0x00C1, PTBR_DEAD_ACUTE, PTBR_KEY_A | PTBR_MOD_SHIFT_LEFT},      // Á
    {0x00C2, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_A | PTBR_MOD_SHIFT_LEFT}, // Â
    {0x00C3, PTBR_DEAD_TILDE, PTBR_KEY_A | PTBR_MOD_SHIFT_LEFT},      // Ã
    {0x00C4, PTBR_DEAD_DIAERESIS, PTBR_KEY_A | PTBR_MOD_SHIFT_LEFT},  // Ä
    // uppercase c
    {0x00C7, PTBR_CEDILLA | PTBR_MOD_SHIFT_LEFT, 0}, // Ç
    // uppercase e
    {0x00C8, PTBR_DEAD_GRAVE, PTBR_KEY_E | PTBR_MOD_SHIFT_LEFT},      // È
    {0x00C9, PTBR_DEAD_ACUTE, PTBR_KEY_E | PTBR_MOD_SHIFT_LEFT},      // É
    {0x00CA, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_E | PTBR_MOD_SHIFT_LEFT}, // Ê
    {0x00CB, PTBR_DEAD_DIAERESIS, PTBR_KEY_E | PTBR_MOD_SHIFT_LEFT},  // Ë
    // uppercase i
    {0x00CC, PTBR_DEAD_GRAVE, PTBR_KEY_I | PTBR_MOD_SHIFT_LEFT},      // Ì
    {0x00CD, PTBR_DEAD_ACUTE, PTBR_KEY_I | PTBR_MOD_SHIFT_LEFT},      // Í
    {0x00CE, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_I | PTBR_MOD_SHIFT_LEFT}, // Î
    {0x00CF, PTBR_DEAD_DIAERESIS, PTBR_KEY_I | PTBR_MOD_SHIFT_LEFT},  // Ï
    // uppercase n
    {0x00D1, PTBR_DEAD_TILDE, PTBR_KEY_N | PTBR_MOD_SHIFT_LEFT}, // Ñ
    // uppercase o
    {0x00D2, PTBR_DEAD_GRAVE, PTBR_KEY_O | PTBR_MOD_SHIFT_LEFT},      // Ò
    {0x00D3, PTBR_DEAD_ACUTE, PTBR_KEY_O | PTBR_MOD_SHIFT_LEFT},      // Ó
    {0x00D4, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_O | PTBR_MOD_SHIFT_LEFT}, // Ô
    {0x00D5, PTBR_DEAD_TILDE, PTBR_KEY_O | PTBR_MOD_SHIFT_LEFT},      // Õ
    {0x00D6, PTBR_DEAD_DIAERESIS, PTBR_KEY_O | PTBR_MOD_SHIFT_LEFT},  // Ö
    // uppercase u
    {0x00D9, PTBR_DEAD_GRAVE, PTBR_KEY_U | PTBR_MOD_SHIFT_LEFT},      // Ù
    {0x00DA, PTBR_DEAD_ACUTE, PTBR_KEY_U | PTBR_MOD_SHIFT_LEFT},      // Ú
    {0x00DB, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_U | PTBR_MOD_SHIFT_LEFT}, // Û
    {0x00DC, PTBR_DEAD_DIAERESIS, PTBR_KEY_U | PTBR_MOD_SHIFT_LEFT},  // Ü
    // uppercase y
    {0x00DD, PTBR_DEAD_ACUTE, PTBR_KEY_Y | PTBR_MOD_SHIFT_LEFT},     // Ý
    {0x0178, PTBR_DEAD_DIAERESIS, PTBR_KEY_Y | PTBR_MOD_SHIFT_LEFT}, // Ÿ
    // Latin Extended-A (nasal vowels used in Portuguese loanwords and
    // indigenous names). These are two-byte UTF-8 sequences (0xC4 / 0xC5).
    {0x0128, PTBR_DEAD_TILDE, PTBR_KEY_I | PTBR_MOD_SHIFT_LEFT}, // Ĩ
    {0x0129, PTBR_DEAD_TILDE, PTBR_KEY_I},                       // ĩ
    {0x0168, PTBR_DEAD_TILDE, PTBR_KEY_U | PTBR_MOD_SHIFT_LEFT}, // Ũ
    {0x0169, PTBR_DEAD_TILDE, PTBR_KEY_U},                       // ũ
    {0x1EBC, PTBR_DEAD_TILDE, PTBR_KEY_E | PTBR_MOD_SHIFT_LEFT}, // Ẽ
    {0x1EBD, PTBR_DEAD_TILDE, PTBR_KEY_E},                       // ẽ
    // Standalone accents: dead key followed by space.
    {0x00B4, PTBR_DEAD_ACUTE, PTBR_KEY_SPACE},      // ´
    {0x00A8, PTBR_DEAD_DIAERESIS, PTBR_KEY_SPACE},  // ¨
    {0x0060, PTBR_DEAD_GRAVE, PTBR_KEY_SPACE},      // ` (ASCII)
    {0x005E, PTBR_DEAD_CIRCUMFLEX, PTBR_KEY_SPACE}, // ^ (ASCII)
    {0x007E, PTBR_DEAD_TILDE, PTBR_KEY_SPACE},      // ~ (ASCII)
    // Remaining ABNT2 symbols reachable with AltGr.
    {0x00A7, 0x2E | PTBR_MOD_ALT_RIGHT, 0}, // §  AltGr+=
    {0x00B0, 0x08 | PTBR_MOD_ALT_RIGHT, 0}, // °  AltGr+E
    {0x00A2, 0x22 | PTBR_MOD_ALT_RIGHT, 0}, // ¢  AltGr+5
    {0x00AA, 0x30 | PTBR_MOD_ALT_RIGHT, 0}, // ª  AltGr+]
    {0x00BA, 0x31 | PTBR_MOD_ALT_RIGHT, 0}, // º  AltGr+backslash
};

#define PTBR_ACCENT_COUNT (sizeof(_accent_map) / sizeof(_accent_map[0]))

// Send one packed stroke: low byte = keycode, high byte = modifier bitmap.
static void _sendStroke(uint16_t stroke) {
    SparktypeKeyboardPTBR.sendKeyStroke((uint8_t)(stroke & 0xFF),
                                        (uint8_t)((stroke >> 8) & 0xFF));
}

// Emit a single codepoint using the ABNT2 accent table.
static void _sendCodepoint(uint16_t codepoint) {
    for (uint8_t i = 0; i < PTBR_ACCENT_COUNT; i++) {
        if (pgm_read_word(&_accent_map[i].codepoint) != codepoint) {
            continue;
        }

        uint16_t stroke1 = pgm_read_word(&_accent_map[i].stroke1);
        uint16_t stroke2 = pgm_read_word(&_accent_map[i].stroke2);

        if (stroke1) {
            _sendStroke(stroke1);
        }
        if (stroke2) {
            _sendStroke(stroke2);
        }
        return;
    }
}

size_t SparktypeKeyboard::write(uint8_t chr) {
    static uint8_t pending = 0;
    static uint16_t codepoint = 0;

    if (pending) {
        if ((chr & 0xC0) != 0x80) {
            // Invalid continuation: drop the pending sequence and handle this
            // byte as the start of a new one.
            pending = 0;
            codepoint = 0;
        } else {
            codepoint = (codepoint << 6) | (chr & 0x3F);

            if (--pending == 0) {
                _sendCodepoint(codepoint);
            }
            return 1;
        }
    }

    if (chr < 0x80) {
        // Standalone accents are emitted as dead key + space so the literal
        // character shows up on every ABNT2 host.
        if (chr == 0x60 || chr == 0x5E || chr == 0x7E) {
            _sendCodepoint(chr);
        } else {
            _sendStroke(pgm_read_word_near(_ascii_map + chr));
        }
        return 1;
    }

    if ((chr & 0xE0) == 0xC0) { // 2-byte sequence
        codepoint = chr & 0x1F;
        pending = 1;
        return 1;
    }

    if ((chr & 0xF0) == 0xE0) { // 3-byte sequence
        codepoint = chr & 0x0F;
        pending = 2;
        return 1;
    }

    if ((chr & 0xF8) == 0xF0) { // 4-byte sequence
        codepoint = chr & 0x07;
        pending = 3;
        return 1;
    }

    // Stray continuation byte or invalid lead: ignore.
    return 1;
}

void SparktypeKeyboard::sendKeyReport(unsigned char *array,
                                      const unsigned int size) {
    while (!usbInterruptIsReady()) {
        // Note: We wait until we can send keyPress
        //       so we know the previous keyPress was
        //       sent.
        usbPoll();
        _delay_ms(5);
    }

    usbSetInterrupt(array, size);
}

SparktypeKeyboard SparktypeKeyboardPTBR = SparktypeKeyboard();
