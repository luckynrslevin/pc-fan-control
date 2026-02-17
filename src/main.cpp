#include <Arduino.h>
#include "fan_control.h"

const uint8_t PIN_PWM    = 9;   // OC1A – Timer1 PWM output
const uint8_t PIN_TACHO  = 2;   // INT0 – fan tachometer (input only)
const uint8_t PIN_BUTTON = 3;   // push-button, active LOW

uint8_t dutyPercent = DUTY_INITIAL;
bool lastButtonState = HIGH;
unsigned long lastPressTime = 0;

void setDuty(uint8_t percent) {
    OCR1A = dutyToCompare(percent);
}

void setup() {
    pinMode(PIN_PWM, OUTPUT);
    pinMode(PIN_TACHO, INPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    // Configure Timer1 for 25 kHz phase-correct PWM on OC1A (pin 9)
    TCCR1A = _BV(COM1A1) | _BV(WGM11);            // non-inverting, WGM mode 10
    TCCR1B = _BV(WGM13)  | _BV(CS10);              // phase-correct PWM (ICR1 top), no prescaler
    ICR1   = PWM_TOP;

    setDuty(dutyPercent);
}

void loop() {
    bool buttonState = digitalRead(PIN_BUTTON);

    // Detect falling edge (HIGH → LOW) with debounce
    if (lastButtonState == HIGH && buttonState == LOW) {
        unsigned long now = millis();
        if (debounceAccept(now, lastPressTime)) {
            lastPressTime = now;
            dutyPercent = nextDuty(dutyPercent);
            setDuty(dutyPercent);
        }
    }

    lastButtonState = buttonState;
}
