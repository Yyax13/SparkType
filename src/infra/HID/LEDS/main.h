#ifndef GET_LEDS_H
#define GET_LEDS_H

#include <DigiKeyboard.h>
#include <stdint.h>

typedef struct {
    bool        caps;
    bool        num;
    bool        scrl;
    
    bool        replyReceived;
    uint16_t    replyCount;
    
} LedsState;

LedsState getLedsState();

void ensureCaps(bool expected);
void ensureNum(bool expected);
void ensureScrl(bool expected);

void resetLedsState(LedsState original);
void clearLedResponseState();

#endif