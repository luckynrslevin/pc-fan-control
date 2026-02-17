#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <stdint.h>

const uint16_t PWM_TOP = 320;
const unsigned long DEBOUNCE_MS = 500;
const uint8_t DUTY_STEP = 10;
const uint8_t DUTY_MIN = 10;
const uint8_t DUTY_MAX = 100;
const uint8_t DUTY_INITIAL = 50;

// Convert duty percent (0–100) to Timer1 compare value (0–PWM_TOP)
uint16_t dutyToCompare(uint8_t percent);

// Advance duty by one step, wrapping from max to min.
// Returns the new duty percent.
uint8_t nextDuty(uint8_t currentPercent);

// Evaluate whether a button press should be accepted based on debounce timing.
// Returns true if the press is valid (enough time has elapsed).
bool debounceAccept(unsigned long now, unsigned long lastPress);

#endif
