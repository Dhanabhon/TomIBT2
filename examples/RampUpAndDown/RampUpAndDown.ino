/*
 * Motor Ramp Up and Down Example
 *
 * This example demonstrates the rampUpAndDown functionality using the TomIBT2 library.
 * The motor will automatically ramp up to target speed and then ramp down to stop.
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

// Timing constants
#define RAMP_UP_TIME_MS       3000  // 3 seconds to ramp up
#define RAMP_DOWN_TIME_MS     2000  // 2 seconds to ramp down
#define CYCLE_PAUSE_MS        2000  // 2 seconds pause between cycles

// Create motor object
TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

unsigned long lastCycleStart = 0;
bool directionClockwise = true;
int cycleCount = 0;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("TomIBT2 Ramp Up and Down Example");
  Serial.println("Motor will automatically ramp up and down cyclically");

  // Initialize motor driver
  motor.begin();

  // Set target speed to 75% (191 out of 255)
  motor.setTargetSpeedPercent(75);

  lastCycleStart = millis();
  cycleCount = 1;

  Serial.print("Cycle ");
  Serial.print(cycleCount);
  Serial.print(" - Direction: ");
  Serial.println(directionClockwise ? "CW" : "CCW");
}

void loop() {
  unsigned long currentTime = millis();

  // Check if we should start a new cycle
  if (!motor.isRamping() && !motor.isMoving()) {
    if (currentTime - lastCycleStart >= CYCLE_PAUSE_MS) {
      // Start new cycle
      directionClockwise = !directionClockwise; // Alternate direction
      cycleCount++;
      lastCycleStart = currentTime;

      Serial.print("Cycle ");
      Serial.print(cycleCount);
      Serial.print(" - Direction: ");
      Serial.println(directionClockwise ? "CW" : "CCW");

      // Reset target speed for new cycle
      motor.setTargetSpeedPercent(75);
    }
  }

  // Execute ramp up and down sequence
  if (motor.isRamping() || motor.isMoving() ||
      (currentTime - lastCycleStart < CYCLE_PAUSE_MS && cycleCount > 1)) {

    motor.rampUpAndDown(
      directionClockwise ? TomIBT2::CW : TomIBT2::CCW,
      RAMP_UP_TIME_MS,
      RAMP_DOWN_TIME_MS
    );
  }

  // Print status every 250ms
  static unsigned long lastPrint = 0;
  if (currentTime - lastPrint >= 250) {
    lastPrint = currentTime;

    Serial.print("Cycle: ");
    Serial.print(cycleCount);
    Serial.print(" | Speed: ");
    Serial.print(motor.getCurrentSpeed());
    Serial.print(" (");
    Serial.print(motor.getCurrentSpeedPercent());
    Serial.print("%) | Direction: ");

    switch (motor.getCurrentDirection()) {
      case TomIBT2::CW:
        Serial.print("CW");
        break;
      case TomIBT2::CCW:
        Serial.print("CCW");
        break;
      default:
        Serial.print("UNKNOWN");
        break;
    }

    Serial.print(" | Status: ");
    if (motor.isRamping()) {
      Serial.print("RAMPING");
    } else if (motor.isMoving()) {
      Serial.print("MOVING");
    } else {
      Serial.print("STOPPED");
    }

    Serial.print(" | Time in cycle: ");
    Serial.print((currentTime - lastCycleStart) / 1000.0, 1);
    Serial.println("s");
  }

  delay(10); // Small delay for stability
}