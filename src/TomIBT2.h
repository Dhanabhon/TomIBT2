/*
 * This file written by Tom Dhanabhon on Jan 13, 2023
*/

#ifndef _____TomIBT2__
#define _____TomIBT2__

#include <Arduino.h>

/*
 * IBT-2
 * Usage 1:
 * VCC pick MCU 5V power supply, GND connected microcontroller GND
 * R_EN and L_EN shorted and connected to 5 level, the drive to work.
 * L_PWM, input PWM signal or high motor forward
 * R_PWM, input PWM signal or high motor reversal
 * 
 * Usage 2:
 * VCC pick MCU 5V power supply, GND connected microcontroller GND
 * R_EN and L_EN short circuit and PWM signal input connected to high-speed
 * L_PWM, pin input 5V level motor is transferred
 * R_PWM, pin input 5V level motor reversal
*/

class TomIBT2 {
    public:
        enum Direction {
            CW = 1,     // clockwise
            CCW = 2,    // counter clockwise
            UNKNOWN = 3,
        };

        TomIBT2(byte r_en_pin, byte l_en_pin, byte rpwm_pin, byte lpwm_pin);
        void begin(void);

        void rampUp(Direction direction, unsigned long timeoutMs);    // Pass in a timeout in milliseconds for how long it will take to ramp from the current speed to full speed with a linear transition.
        void rampDown(unsigned long timeoutMs);

        void rotate(int speed, Direction direction);
        void stop(void);    // Stop the motor by allowing coasting.
        void brake(void);   // Stop the motor with braking action.

        void setTargetSpeed(int speed);
        void setTargetSpeedPercent(int percent);

        int getCurrentSpeed(void);
        int getCurrentSpeedPercent(void);
        Direction getCurrentDirection(void);

    private:
        byte R_EN_PIN;  // Forward drive enable input, high enable, low close
        byte L_EN_PIN;  // Reverse drive enable input, high enable, low close
        byte RPWM_PIN;  // Forward level or PWM signal input, active high
        byte LPWM_PIN;  // Inversion level or PWM signale input, active high
        byte R_IS;      // Forward drive - side current alarm ouput (Unused)
        byte L_IS;      // Reverse drive -side current alarm output (Unused)

        byte MAX_SPEED = 255;   // 100% duty cycle

        unsigned long currentMillis = 0;
        unsigned long previousMillis = 0; 

        int currentSpeed = 0;
        int targetSpeed = MAX_SPEED;
        Direction currentDirection = UNKNOWN;
};

#endif