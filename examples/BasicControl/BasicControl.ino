/*
 * Basic Motor Control Example
 *
 * This example demonstrates basic motor control using the TomIBT2 library.
 * The motor will rotate clockwise at full speed continuously.
 *
 * Circuit:
 * - Connect IBT-2 R_EN to pin 7
 * - Connect IBT-2 L_EN to pin 8
 * - Connect IBT-2 RPWM to pin 10 (PWM capable)
 * - Connect IBT-2 LPWM to pin 9 (PWM capable)
 * - Connect IBT-2 VCC to Arduino 5V
 * - Connect IBT-2 GND to Arduino GND
 * - Connect motor to IBT-2 B+ and B- terminals
 * - Connect motor power supply to IBT-2 M+ and M- terminals
 */

#include <TomIBT2.h>

// Pin definitions for IBT-2 motor driver
#define MOTOR_PIN_R_EN        7   // Forward drive enable
#define MOTOR_PIN_L_EN        8   // Reverse drive enable
#define MOTOR_PIN_RPWM        10  // Forward PWM (490.20Hz)
#define MOTOR_PIN_LPWM        9   // Reverse PWM (490.20Hz)

// Create motor object
TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("TomIBT2 Basic Control Example");

  // Initialize motor driver
  motor.begin();

  Serial.println("Motor initialized. Starting rotation...");
}

void loop() {
  // Rotate motor clockwise at full speed (255)
  motor.rotate(255, TomIBT2::CW);

  // Optional: Print current motor status
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint >= 1000) { // Every second
    lastPrint = millis();
    Serial.print("Speed: ");
    Serial.print(motor.getCurrentSpeed());
    Serial.print(" (");
    Serial.print(motor.getCurrentSpeedPercent());
    Serial.print("%) Direction: ");
    Serial.println(motor.getCurrentDirection() == TomIBT2::CW ? "CW" : "CCW");
  }

  delay(10); // Small delay for stability
}