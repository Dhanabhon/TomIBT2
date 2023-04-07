# TomIBT2

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/dhanabhon/library/TomIBT2.svg)](https://registry.platformio.org/libraries/dhanabhon/TomIBT2) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)

TomIBT2 is an Arduino library for controlling the IBT-2 (H-Bridge) motor driver board.

### Interfacing IBT-2 H-Bridge with Arduino
#### Method 1:
- VCC pick MCU 5V power supply, GND connected microcontroller GND
- R_EN and L_EN shorted and connected to 5 level, the drive to work.
- L_PWM, input PWM signal or high motor forward
- R_PWM, input PWM signal or high motor reversal

#### Method 2:
- VCC pick MCU 5V power supply, GND connected microcontroller GND
- R_EN and L_EN short circuit and PWM signal input connected to high-speed
- L_PWM, pin input 5V level motor is transferred
- R_PWM, pin input 5V level motor reversal

### Example
```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10  // PWM 490.20Hz
#define MOTOR_PIN_LPWM        9   // PWM 490.20Hz

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {
    rotateMotor(255, TomIBT2::CW, 2000);
}

void rotateMotor(int speed, TomIBT2::Direction direction, long rampTimeMs = 1000) {
  motor.setTargetSpeed(speed);
  motor.rampUp(direction, rampTimeMs);
}
```
