#include "main.h"
#include <DigiKeyboard.h>
#include <avr/sleep.h>

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

void shutdevice() {
    disconnectDevice();

    USB_INTR_ENABLE &= ~(1 << USB_INTR_ENABLE_BIT);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();

    ADCSRA &= ~(1 << ADEN);

    cli();
    sleep_cpu();
}
