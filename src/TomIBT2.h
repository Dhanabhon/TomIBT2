/*
 * TomIBT2 Arduino Library - IBT-2 H-Bridge Motor Driver Controller
 *
 * This library provides comprehensive control for IBT-2 motor driver boards,
 * including basic rotation, speed ramping, braking, and state monitoring.
 *
 * Author: Tom Dhanabhon
 * Created: Jan 13, 2023
 * Updated: 2025
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
        /// Motor rotation direction enumeration
        enum Direction {
            CW = 1,     ///< Clockwise rotation
            CCW = 2,    ///< Counter-clockwise rotation
            UNKNOWN = 3 ///< Unknown/unset direction
        };

        /// Constructor - Initialize motor with pin assignments
        /// @param r_en_pin Forward drive enable pin (HIGH = enable, LOW = disable)
        /// @param l_en_pin Reverse drive enable pin (HIGH = enable, LOW = disable)
        /// @param rpwm_pin Forward PWM signal pin (active high)
        /// @param lpwm_pin Reverse PWM signal pin (active high)
        TomIBT2(byte r_en_pin, byte l_en_pin, byte rpwm_pin, byte lpwm_pin);

        /// Initialize the motor driver pins and set initial state
        void begin(void);

        /// Gradually increase motor speed to target with linear transition
        /// @param direction Motor rotation direction (CW or CCW)
        /// @param timeoutMs Time in milliseconds for complete ramp-up
        void rampUp(Direction direction, unsigned long timeoutMs);

        /// Gradually decrease motor speed to zero with linear transition
        /// @param timeoutMs Time in milliseconds for complete ramp-down
        void rampDown(unsigned long timeoutMs);

        /// Perform ramp up followed by ramp down sequence
        /// @param direction Motor rotation direction (CW or CCW)
        /// @param rampUpTimeoutMs Time for ramp-up phase in milliseconds
        /// @param rampDownTimeoutMs Time for ramp-down phase in milliseconds
        void rampUpAndDown(Direction direction, unsigned long rampUpTimeoutMs, unsigned long rampDownTimeoutMs);

        /// Rotate motor at specified speed and direction
        /// @param speed Motor speed (0-255, automatically clamped to valid range)
        /// @param direction Motor rotation direction (CW or CCW)
        void rotate(int speed, Direction direction);

        /// Stop motor by disabling drive (allows coasting)
        void stop(void);

        /// Stop motor with active braking (immediate stop)
        void brake(void);

        /// Set target speed for ramping operations
        /// @param speed Target speed value (0-255, automatically clamped)
        void setTargetSpeed(int speed);

        /// Set target speed as percentage for ramping operations
        /// @param percent Target speed percentage (0-100, automatically clamped)
        void setTargetSpeedPercent(int percent);

        /// Get current motor speed
        /// @return Current speed value (0-255)
        int getCurrentSpeed(void) const;

        /// Get current motor speed as percentage
        /// @return Current speed percentage (0-100)
        int getCurrentSpeedPercent(void) const;

        /// Get current motor rotation direction
        /// @return Current direction (CW, CCW, or UNKNOWN)
        Direction getCurrentDirection(void) const;

        /// Check if motor is currently ramping (up or down)
        /// @return true if ramping is in progress, false otherwise
        bool isRamping(void) const;

        /// Check if motor is currently moving (speed > 0)
        /// @return true if motor is moving, false if stopped
        bool isMoving(void) const;

    private:
        // Hardware pin assignments
        byte R_EN_PIN;  ///< Forward drive enable pin (HIGH = enable, LOW = disable)
        byte L_EN_PIN;  ///< Reverse drive enable pin (HIGH = enable, LOW = disable)
        byte RPWM_PIN;  ///< Forward PWM signal pin (active high)
        byte LPWM_PIN;  ///< Reverse PWM signal pin (active high)

        // Speed constants
        static const byte MAX_SPEED = 255;   ///< Maximum speed (100% duty cycle)
        static const byte MIN_SPEED = 0;     ///< Minimum speed (0% duty cycle)

        // Timing and state variables
        unsigned long previousMillis;        ///< Last update timestamp for ramping
        bool isRampingUp;                   ///< Flag indicating ramp-up in progress
        bool isRampingDown;                 ///< Flag indicating ramp-down in progress

        // Motor state
        int currentSpeed;                   ///< Current motor speed (0-255)
        int targetSpeed;                    ///< Target speed for ramping operations
        Direction currentDirection;         ///< Current rotation direction

        // Private helper methods
        /// Validate if a pin number is valid for Arduino
        /// @param pin Pin number to validate
        /// @return true if pin is valid, false otherwise
        bool validatePin(byte pin) const;

        /// Update motor output based on current speed and direction
        void updateMotorOutput(); 

};

#endif