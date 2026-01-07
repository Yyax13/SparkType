#include "main.h"
#include <DigiKeyboard.h>

#include "../LEDS/main.h"

void reconnectDevice() {
    DigiKeyboard.delay(500);
    disconnectDevice();
    connectDevice();
    
}

void disconnectDevice() {
    DigiKeyboard.delay(500);
    clearLedResponseState();
    cli();
    g_hostConfigRequestCount = 0;
    sei();
    
    DigiKeyboard.delay(300);
    usbDeviceDisconnect();
    DigiKeyboard.delay(1200);
    
}

void connectDevice() {
    DigiKeyboard.delay(500);
    clearLedResponseState();
    cli();
    g_hostConfigRequestCount = 0;
    sei();
    
    DigiKeyboard.delay(300);
    usbDeviceConnect();
    DigiKeyboard.delay(1200);

}