# pc-fan-control

## Version

V0.1

## Date
2026-02-16

------

## 1. Purpose and Scope
This is a simple arduino based project to control the speed of a PWM based PC fan.

## 2. System overview
### 2.1. General
- Arduino Pro Mini 5 volts micro controller
- An PWM based PC fan. Mine is from an old MAC and has 4 wires.
- 12 volts power supply
- Button to change the speed of the fan in several steps (e.g. 10%, 20%, ..., 100%)
- Platform.io as development environment

### 2.1. Wiring diagram
![Arduino Pro Mini PWM Fan Wiring](wiring-sketch.svg)

# 3. Requirements

## 3.1 Functional requirements
**FR-0001**
The system shall start with a duty cacle of 50% when powered up.

**FR-0002**
Each time the button is pushed, the system shall increase the duty cycle by 10% and after reaching 100% start over with 10%.

## 3.1 Non-Functional requirements
**NFR-0001**
The system shall be buildable via PlatformIO CLI without requiring an IDE.

**NFR-0002**
The system shall be resilliant to multible button signals received within one time the user actually pushes the button. Multiple signals within the duration of 500 ms can be interpreted as one single button press.
