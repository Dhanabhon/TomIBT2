/*
 * Motor Ramping Control Example
 *
 * This example demonstrates motor ramping functionality using the TomIBT2 library.
 * The motor will ramp up to target speed, maintain it, then ramp down.
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
#define RAMP_UP_TIME_MS       2000  // 2 seconds to ramp up
#define RAMP_DOWN_TIME_MS     1500  // 1.5 seconds to ramp down
#define RUN_TIME_MS           3000  // 3 seconds at full speed
#define PAUSE_TIME_MS         2000  // 2 seconds pause between cycles

// Create motor object
TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

// State machine variables
enum MotorState {
  STATE_RAMPING_UP,
  STATE_RUNNING,
  STATE_RAMPING_DOWN,
  STATE_PAUSED
};

MotorState currentState = STATE_RAMPING_UP;
unsigned long stateStartTime = 0;
bool directionClockwise = true;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  Serial.println("TomIBT2 Ramping Control Example");
  Serial.println("Motor will ramp up, run, ramp down, and pause cyclically");

  // Initialize motor driver
  motor.begin();

  // Set target speed to 80% (204 out of 255)
  motor.setTargetSpeedPercent(80);

  stateStartTime = millis();
  Serial.println("Starting ramp up sequence...");
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - stateStartTime;

  switch (currentState) {
    case STATE_RAMPING_UP:
      // Call rampUp repeatedly until target speed is reached
      motor.rampUp(directionClockwise ? TomIBT2::CW : TomIBT2::CCW, RAMP_UP_TIME_MS);

      if (!motor.isRamping() || elapsedTime >= RAMP_UP_TIME_MS + 500) {
        currentState = STATE_RUNNING;
        stateStartTime = currentTime;
        Serial.println("Ramp up complete. Running at target speed...");
      }
      break;

    case STATE_RUNNING:
      // Maintain current speed
      if (elapsedTime >= RUN_TIME_MS) {
        currentState = STATE_RAMPING_DOWN;
        stateStartTime = currentTime;
        Serial.println("Starting ramp down sequence...");
      }
      break;

    case STATE_RAMPING_DOWN:
      // Call rampDown repeatedly until motor stops
      motor.rampDown(RAMP_DOWN_TIME_MS);

      if (!motor.isRamping() || elapsedTime >= RAMP_DOWN_TIME_MS + 500) {
        currentState = STATE_PAUSED;
        stateStartTime = currentTime;
        directionClockwise = !directionClockwise; // Alternate direction
        Serial.print("Ramp down complete. Pausing... Next direction: ");
        Serial.println(directionClockwise ? "CW" : "CCW");
      }
      break;

    case STATE_PAUSED:
      // Pause between cycles
      if (elapsedTime >= PAUSE_TIME_MS) {
        currentState = STATE_RAMPING_UP;
        stateStartTime = currentTime;
        motor.setTargetSpeedPercent(80); // Reset target speed
        Serial.println("Starting new cycle - ramp up sequence...");
      }
      break;
  }

  // Print status every 500ms
  static unsigned long lastPrint = 0;
  if (currentTime - lastPrint >= 500) {
    lastPrint = currentTime;

    Serial.print("State: ");
    switch (currentState) {
      case STATE_RAMPING_UP: Serial.print("RAMP_UP"); break;
      case STATE_RUNNING: Serial.print("RUNNING"); break;
      case STATE_RAMPING_DOWN: Serial.print("RAMP_DOWN"); break;
      case STATE_PAUSED: Serial.print("PAUSED"); break;
    }

    Serial.print(" | Speed: ");
    Serial.print(motor.getCurrentSpeed());
    Serial.print(" (");
    Serial.print(motor.getCurrentSpeedPercent());
    Serial.print("%) | Direction: ");
    Serial.print(motor.getCurrentDirection() == TomIBT2::CW ? "CW" :
                 motor.getCurrentDirection() == TomIBT2::CCW ? "CCW" : "UNKNOWN");
    Serial.print(" | Ramping: ");
    Serial.println(motor.isRamping() ? "YES" : "NO");
  }

  delay(10); // Small delay for stability
}