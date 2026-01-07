#ifndef BLINK_ALERT_H
#define BLINK_ALERT_H

/// Receive `int times`, every time takes a second to run
void blinkAlert(int times);

/// Min ms: 50;
/// Min times: 1;
void blinkMs(int ms, int times);

#endif