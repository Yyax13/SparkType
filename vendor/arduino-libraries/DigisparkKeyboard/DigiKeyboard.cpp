#include "DigiKeyboard.h"

static uchar idleRate;
volatile uchar g_keyboardLeds = 0;
static uchar g_ledWriteRemaining = 0;
volatile bool g_ledReplyReceived = false;
volatile uint16_t g_ledReplyCount = 0;


const PROGMEM uchar usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {
    0x05, 0x01,
    0x09, 0x06,
    0xa1, 0x01,

    0x05, 0x07,
    0x19, 0xe0,
    0x29, 0xe7,
    0x15, 0x00,
    0x25, 0x01,
    0x75, 0x01,
    0x95, 0x08,
    0x81, 0x02,

    0x95, 0x01,
    0x75, 0x08,
    0x25, 0x73,
    0x19, 0x00,
    0x29, 0x73,
    0x81, 0x00,

    0x05, 0x08,
    0x19, 0x01,
    0x29, 0x05,
    0x15, 0x00,
    0x25, 0x01,
    0x95, 0x05,
    0x75, 0x01,
    0x91, 0x02,

    0x95, 0x01,
    0x75, 0x03,
    0x91, 0x01,

    0xc0

};

DigiKeyboardDevice DigiKeyboard = DigiKeyboardDevice();

#ifdef __cplusplus
extern "C" {
#endif

uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t *rq = (usbRequest_t *)((void *)data);

    usbMsgPtr = DigiKeyboard.reportBuffer;

    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
        if (rq->bRequest == USBRQ_HID_GET_REPORT) {
            return 0;

        }

        if (rq->bRequest == USBRQ_HID_GET_IDLE) {
            return 0;

        }

        if (rq->bRequest == USBRQ_HID_SET_IDLE) {
            idleRate = rq->wValue.bytes[1];
            return 0;

        }

        if (rq->bRequest == USBRQ_HID_SET_REPORT) {
            g_ledWriteRemaining = rq->wLength.word;
            return USB_NO_MSG;

        }
    }

    return 0;

}

uchar usbFunctionWrite(uchar *data, uchar len) {
    if (g_ledWriteRemaining == 0) {
        return 1;
    }

    if (len > g_ledWriteRemaining) {
        len = g_ledWriteRemaining;
    }

    g_keyboardLeds = data[0];
    g_ledReplyReceived = true;
    g_ledReplyCount++;

    g_ledWriteRemaining -= len;

    return (g_ledWriteRemaining == 0);
}


#ifdef __cplusplus
}
#endif