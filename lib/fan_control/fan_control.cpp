#include "fan_control.h"

uint16_t dutyToCompare(uint8_t percent) {
    return (uint16_t)percent * PWM_TOP / 100;
}

uint8_t nextDuty(uint8_t currentPercent) {
    uint8_t next = currentPercent + DUTY_STEP;
    if (next > DUTY_MAX) {
        next = DUTY_MIN;
    }
    return next;
}

bool debounceAccept(unsigned long now, unsigned long lastPress) {
    return (now - lastPress) >= DEBOUNCE_MS;
}
