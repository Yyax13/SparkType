//Mapeado original por Eduardo Gadotti https://github.com/Gadotti em 27/07/2020
//Updates e alterações por Yyax13 https://github.com/Yyax13 em 06/01/2026

#ifndef DIGIKEYBOARDPTBR_H
#define DIGIKEYBOARDPTBR_H

#include <stdint.h>
#include <stddef.h>
#include <DigiKeyboard.h>

#define PTBR_MOD_CONTROL_LEFT (1 << 8)
#define PTBR_MOD_SHIFT_LEFT (1 << 9)
#define PTBR_MOD_ALT_LEFT (1 << 10)
#define PTBR_MOD_GUI_LEFT (1 << 11)
#define PTBR_MOD_CONTROL_RIGHT (1 << 12)
#define PTBR_MOD_SHIFT_RIGHT (1 << 13)
#define PTBR_MOD_ALT_RIGHT (1 << 14)
#define PTBR_MOD_GUI_RIGHT (1 << 15)

class DigiKeyboardDevicePtBr : public DigiKeyboardDevice {
public:
    size_t write(uint8_t chr);
    void sendKeyReport(unsigned char *array, const unsigned int size);
};

extern DigiKeyboardDevicePtBr DigiKeyboardPtBr;

#endif
