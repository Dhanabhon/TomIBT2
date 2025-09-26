#include "TomIBT2.h"

// Constructor
TomIBT2::TomIBT2(byte r_en_pin, byte l_en_pin, byte rpwm_pin, byte lpwm_pin)
    : R_EN_PIN(r_en_pin), L_EN_PIN(l_en_pin), RPWM_PIN(rpwm_pin), LPWM_PIN(lpwm_pin),
      previousMillis(0), currentSpeed(0), targetSpeed(MAX_SPEED),
      currentDirection(UNKNOWN), isRampingUp(false), isRampingDown(false) {
}

void TomIBT2::begin(void) {
    if (!validatePin(R_EN_PIN) || !validatePin(L_EN_PIN) ||
        !validatePin(RPWM_PIN) || !validatePin(LPWM_PIN)) {
        return; // Invalid pin configuration
    }

    pinMode(R_EN_PIN, OUTPUT);
    pinMode(L_EN_PIN, OUTPUT);
    pinMode(RPWM_PIN, OUTPUT);
    pinMode(LPWM_PIN, OUTPUT);

    // Ensure motor is stopped initially
    stop();
}

void TomIBT2::rotate(int speed, Direction direction) {
    if (direction == UNKNOWN) {
        return; // Invalid direction
    }

    // Clamp speed to valid range
    speed = constrain(speed, MIN_SPEED, MAX_SPEED);

    // Stop any ongoing ramping
    isRampingUp = false;
    isRampingDown = false;

    currentDirection = direction;
    currentSpeed = speed;
    targetSpeed = speed;

    updateMotorOutput();
}

void TomIBT2::stop(void) {
    digitalWrite(R_EN_PIN, LOW);
    digitalWrite(L_EN_PIN, LOW);

    currentSpeed = 0;
    targetSpeed = 0;
    isRampingUp = false;
    isRampingDown = false;

    analogWrite(RPWM_PIN, 0);
    analogWrite(LPWM_PIN, 0);
}

void TomIBT2::brake(void) {
    digitalWrite(R_EN_PIN, HIGH);
    digitalWrite(L_EN_PIN, HIGH);

    currentSpeed = 0;
    targetSpeed = 0;
    isRampingUp = false;
    isRampingDown = false;

    analogWrite(RPWM_PIN, 0);
    analogWrite(LPWM_PIN, 0);
}

int TomIBT2::getCurrentSpeed(void) const {
    return currentSpeed;
}

int TomIBT2::getCurrentSpeedPercent(void) const {
    return int((currentSpeed * 100.0) / MAX_SPEED);
}

TomIBT2::Direction TomIBT2::getCurrentDirection(void) const {
    return currentDirection;
}

bool TomIBT2::isRamping(void) const {
    return isRampingUp || isRampingDown;
}

bool TomIBT2::isMoving(void) const {
    return currentSpeed > 0;
}

void TomIBT2::setTargetSpeed(int speed) {
    targetSpeed = constrain(speed, MIN_SPEED, MAX_SPEED);
}

void TomIBT2::setTargetSpeedPercent(int percent) {
    percent = constrain(percent, 0, 100);
    targetSpeed = map(percent, 0, 100, MIN_SPEED, MAX_SPEED);
}

void TomIBT2::rampUp(Direction direction, unsigned long timeoutMs) {
    if (direction == UNKNOWN || timeoutMs == 0) {
        return; // Invalid parameters
    }

    if (!isRampingUp) {
        // Initialize ramping
        currentDirection = direction;
        isRampingUp = true;
        isRampingDown = false;
        previousMillis = millis();
    }

    unsigned long currentMillis = millis();
    unsigned long stepInterval = timeoutMs / (targetSpeed - currentSpeed + 1);

    if (currentMillis - previousMillis >= stepInterval) {
        previousMillis = currentMillis;

        if (currentSpeed < targetSpeed) {
            currentSpeed++;
            updateMotorOutput();
        } else {
            isRampingUp = false; // Ramping complete
        }
    }
}

void TomIBT2::rampDown(unsigned long timeoutMs) {
    if (timeoutMs == 0 || currentSpeed == 0) {
        return; // Invalid parameters or already stopped
    }

    if (!isRampingDown) {
        // Initialize ramping down
        isRampingDown = true;
        isRampingUp = false;
        previousMillis = millis();
    }

    unsigned long currentMillis = millis();
    unsigned long stepInterval = timeoutMs / (currentSpeed + 1);

    if (currentMillis - previousMillis >= stepInterval) {
        previousMillis = currentMillis;

        if (currentSpeed > 0) {
            currentSpeed--;
            updateMotorOutput();
        } else {
            isRampingDown = false;
            stop(); // Complete stop when reaching zero
        }
    }
}

void TomIBT2::rampUpAndDown(Direction direction, unsigned long rampUpTimeoutMs, unsigned long rampDownTimeoutMs) {
    if (direction == UNKNOWN || rampUpTimeoutMs == 0 || rampDownTimeoutMs == 0) {
        return; // Invalid parameters
    }

    // First ramp up to target speed
    if (currentSpeed < targetSpeed) {
        rampUp(direction, rampUpTimeoutMs);
    }
    // Then ramp down to zero
    else if (currentSpeed > 0 && !isRampingUp) {
        rampDown(rampDownTimeoutMs);
    }
}

// Private helper methods
bool TomIBT2::validatePin(byte pin) const {
    // Basic pin validation for Arduino Uno/Nano (adjust for other boards)
    return (pin >= 0 && pin <= 13) || (pin >= A0 && pin <= A5);
}

void TomIBT2::updateMotorOutput() {
    if (currentSpeed == 0) {
        // Stop the motor
        digitalWrite(R_EN_PIN, LOW);
        digitalWrite(L_EN_PIN, LOW);
        analogWrite(RPWM_PIN, 0);
        analogWrite(LPWM_PIN, 0);
    } else {
        // Enable motor and set direction
        digitalWrite(R_EN_PIN, HIGH);
        digitalWrite(L_EN_PIN, HIGH);

        if (currentDirection == CW) {
            analogWrite(RPWM_PIN, currentSpeed);
            analogWrite(LPWM_PIN, 0);
        } else if (currentDirection == CCW) {
            analogWrite(RPWM_PIN, 0);
            analogWrite(LPWM_PIN, currentSpeed);
        }
    }
}
