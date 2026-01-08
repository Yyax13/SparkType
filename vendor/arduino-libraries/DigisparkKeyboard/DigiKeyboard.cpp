/*
 * DigiKeyboard.cpp
 *
 * Implementation file separated from DigiKeyboard.h.
 *
 * Based on Obdev's AVRUSB code.
 * Modified for Digispark by Digistump.
 *
 * This file is a derived work due to direct linkage with
 * GPL-licensed V-USB components.
 *
 * Copyright (c) 2026 Yyax13
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
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

    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_STANDARD) {
        if (rq->bRequest == USBRQ_SET_CONFIGURATION ||
            rq->bRequest == USBRQ_GET_DESCRIPTOR ||
            rq->bRequest == USBRQ_SET_IDLE) {
            g_hostConfigRequestCount++;
        }
    }

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
    g_ledWriteRemaining -= len;

    return (g_ledWriteRemaining == 0);
}


#ifdef __cplusplus
}
#endif
