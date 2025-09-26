# TomIBT2 Arduino Library Changelog

## 1.2.0 - 2025

### Major Improvements
- **Fixed function name typo**: Corrected `TomITB2::rampUpAndDown` to `TomIBT2::rampUpAndDown`
- **Completely reimplemented rampUpAndDown function**: Now provides proper sequential ramp-up and ramp-down functionality
- **Enhanced ramping algorithms**: Improved timing and logic for smoother motor transitions
- **Added comprehensive input validation**: Pin validation and parameter bounds checking
- **Improved const correctness**: Added const qualifiers to getter methods
- **Added new state monitoring methods**:
  - `isRamping()` - Check if motor is currently ramping
  - `isMoving()` - Check if motor is currently moving

### Code Quality Improvements
- **Enhanced documentation**: Added comprehensive Doxygen-style comments throughout the codebase
- **Modernized constructor**: Used member initializer lists for better performance
- **Improved error handling**: Added validation for invalid directions and parameters
- **Optimized motor output**: Centralized motor control logic in `updateMotorOutput()` helper method
- **Better memory usage**: Replaced dynamic variables with proper initialization

### Example Updates
- **BasicControl.ino**: Added serial debugging, status monitoring, and better documentation
- **RampUpControl.ino**: Complete rewrite with state machine pattern, alternating directions, and comprehensive status reporting
- **RampUpAndDown.ino**: New example demonstrating the fixed rampUpAndDown functionality

### Breaking Changes
- `getCurrentSpeedPercent()`, `getCurrentSpeed()`, and `getCurrentDirection()` are now const methods
- Improved parameter validation may reject previously accepted invalid inputs

## 1.1.2 - Jun 16, 2023

- Fix the bug where motor rotation
- Update and add new Arduino code example

## 1.1.1 - May 29, 2023

- Fix the bug where ramping down function

## 1.1.0 - May 27, 2023

- Add stopping of the motor feature

## 1.0.1 - Apr 11, 2023

- Fix bug where the submitting of the Arduino registry

## 1.0.0 - Apr 7, 2023

- First version

## 0.0.1 Initial Release