#include "TomIBT2.h"

// Construcstor
TomIBT2::TomIBT2(byte r_en_pin, byte l_en_pin, byte rpwm_pin, byte lpwm_pin) {
    this->R_EN_PIN = r_en_pin;
    this->L_EN_PIN = l_en_pin;
    this->RPWM_PIN = rpwm_pin;
    this->LPWM_PIN = lpwm_pin;
}

void TomIBT2::begin(void) {
    pinMode(this->R_EN_PIN, OUTPUT);
    pinMode(this->L_EN_PIN, OUTPUT);
    pinMode(this->RPWM_PIN, OUTPUT);
    pinMode(this->LPWM_PIN, OUTPUT);
}

void TomIBT2::rotate(int speed, Direction direction) {
    digitalWrite(R_EN_PIN, HIGH);
    digitalWrite(L_EN_PIN, HIGH);

    this->currentDirection = direction;
    this->currentSpeed = speed;

    int pwmPin = (this->currentDirection == CW) ? this->RPWM_PIN : this->LPWM_PIN;

    analogWrite(pwmPin, this->currentSpeed);
}

int TomIBT2::getCurrentSpeed(void) {
    return this->currentSpeed;
}

int TomIBT2::getCurrentSpeedPercent(void) {
    return int((this->currentSpeed / 255.0 * 100.0));
}

TomIBT2::Direction TomIBT2::getCurrentDirection(void) {
    return this->currentDirection;
}

void TomIBT2::setTargetSpeed(int speed) {
    if (speed > MAX_SPEED) {
        speed = MAX_SPEED;
    } else if (speed < 0) {
        speed = 0;
    }

    this->targetSpeed = speed;
}

void TomIBT2::setTargetSpeedPercent(int percent) {
    if (percent > 100) {
        percent = 100;
    } else if (percent < 0) {
        percent = 0;
    }

    this->targetSpeed = map(percent, 0, 100, 0, 255);
}

void TomIBT2::rampUp(Direction direction,  unsigned long timeoutMs) {
    digitalWrite(R_EN_PIN, HIGH);
    digitalWrite(L_EN_PIN, HIGH);

    this->currentDirection = direction;

    int pwmPin = (this->currentDirection == CW) ? this->RPWM_PIN : this->LPWM_PIN;

    this->currentMillis = millis();

    if (this->currentMillis - this->previousMillis >= timeoutMs / (MAX_SPEED - 0)) {
        this->previousMillis = this->currentMillis;
        this->currentSpeed++;

        if (this->currentSpeed >= this->targetSpeed) {
            this->currentSpeed = this->targetSpeed;
        }

        analogWrite(pwmPin, this->currentSpeed);
    }
}

void TomIBT2::rampDown(unsigned long timeoutMs) {
    digitalWrite(R_EN_PIN, HIGH);
    digitalWrite(L_EN_PIN, HIGH);

    int pwmPin = (this->currentDirection == CW) ? this->RPWM_PIN : this->LPWM_PIN;

    this->currentMillis = millis();

    if (this->currentMillis - this->previousMillis >= timeoutMs / (MAX_SPEED - 0)) {
        this->previousMillis = this->currentMillis;
        this->currentSpeed--;

        if (this->currentSpeed <= 0) {
            this->currentSpeed = 0;
        }

        analogWrite(pwmPin, this->currentSpeed);
    }
}