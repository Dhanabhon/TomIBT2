
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
  motor.rotate(255, TomIBT2::CW);
}