# TomIBT2

[![PlatformIO Registry](https://badges.registry.platformio.org/packages/dhanabhon/library/TomIBT2.svg)](https://registry.platformio.org/libraries/dhanabhon/TomIBT2) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT) ![Version](https://img.shields.io/badge/version-1.2.0-blue.svg)

**Enhanced Arduino library for controlling IBT-2 H-Bridge motor driver boards with advanced ramping algorithms, input validation, and comprehensive state monitoring.**

## Features

- **Motor Control**: Basic rotation with speed (0-255) and direction (CW/CCW)
- **Advanced Ramping**: Smooth linear ramp-up and ramp-down transitions
- **Speed Management**: Both absolute (0-255) and percentage (0-100) control
- **State Monitoring**: Real-time speed, direction, and ramping status
- **Input Validation**: Robust parameter and pin validation
- **Multiple Stop Modes**: Coasting stop and active braking
- **Error Handling**: Graceful handling of invalid inputs
- **Cross-Platform**: Arduino, ESP32, ESP8266, STM32, and more

## What's New in v1.2.0

- **Fixed critical bug**: Corrected function name typo in `rampUpAndDown()`
- **Enhanced ramping algorithms**: Improved timing and smoother transitions
- **New state monitoring**: Added `isRamping()` and `isMoving()` methods
- **Better error handling**: Comprehensive input validation
- **Improved documentation**: Full API documentation with examples
- **Modern C++ practices**: Const correctness and member initializers

## Installation

### Arduino IDE
1. Open Arduino IDE
2. Go to **Sketch** → **Include Library** → **Manage Libraries**
3. Search for "TomIBT2"
4. Click **Install**

### PlatformIO
```ini
# platformio.ini
[env]
lib_deps =
    dhanabhon/TomIBT2@^1.2.0
```

Or via CLI:
```bash
pio lib install "TomIBT2"
```

## Hardware Setup

### IBT-2 H-Bridge Board Pinout
```
     _______________________________________
   /                                         \
  |                                           |
  |                                           |
  |       IBT-2 Pinout                       ===
  |                                         | B-|
  |                                          ===
  |                                         | B+|
  |  o  o  GND, VCC                          ===
  |  o  o  IS_R, IS_L                       | M+|
  |  o  o  EN_R, EN_L                        ===
  |  o  o  RPWM, LPWM                       | M-|
  |                                          ===
  |                                           |
   \ _______________________________________ /
```

### Connection Guide

#### Standard Configuration
- **VCC** → Arduino 5V
- **GND** → Arduino GND
- **R_EN** → Digital pin (e.g., pin 7)
- **L_EN** → Digital pin (e.g., pin 8)
- **RPWM** → PWM pin (e.g., pin 10)
- **LPWM** → PWM pin (e.g., pin 9)
- **B+/B-** → Motor terminals
- **M+/M-** → Motor power supply (6-27V)

## Quick Start

### Basic Motor Control
```cpp
#include <TomIBT2.h>

// Pin definitions
#define MOTOR_R_EN    7
#define MOTOR_L_EN    8
#define MOTOR_RPWM    10  // PWM pin
#define MOTOR_LPWM    9   // PWM pin

TomIBT2 motor(MOTOR_R_EN, MOTOR_L_EN, MOTOR_RPWM, MOTOR_LPWM);

void setup() {
  motor.begin();
}

void loop() {
  // Rotate clockwise at full speed
  motor.rotate(255, TomIBT2::CW);
  delay(2000);

  // Rotate counter-clockwise at half speed
  motor.rotate(128, TomIBT2::CCW);
  delay(2000);

  // Stop motor
  motor.stop();
  delay(1000);
}
```

### Advanced Ramping Control
```cpp
#include <TomIBT2.h>

TomIBT2 motor(7, 8, 10, 9);

void setup() {
  Serial.begin(115200);
  motor.begin();

  // Set target speed to 80%
  motor.setTargetSpeedPercent(80);
}

void loop() {
  // Ramp up over 2 seconds
  motor.rampUp(TomIBT2::CW, 2000);

  // Check if ramping is complete
  if (!motor.isRamping() && motor.isMoving()) {
    delay(1000); // Run at full speed

    // Ramp down over 1.5 seconds
    motor.rampDown(1500);
  }

  // Monitor status
  Serial.print("Speed: ");
  Serial.print(motor.getCurrentSpeedPercent());
  Serial.print("% | Ramping: ");
  Serial.println(motor.isRamping() ? "YES" : "NO");

  delay(100);
}
```

## API Reference

### Constructor
```cpp
TomIBT2(byte r_en_pin, byte l_en_pin, byte rpwm_pin, byte lpwm_pin)
```

### Core Methods

#### Initialization
- `void begin()` - Initialize motor driver pins

#### Motor Control
- `void rotate(int speed, Direction direction)` - Immediate motor control
- `void stop()` - Stop motor (coasting)
- `void brake()` - Stop motor (active braking)

#### Ramping Control
- `void rampUp(Direction direction, unsigned long timeoutMs)` - Gradual speed increase
- `void rampDown(unsigned long timeoutMs)` - Gradual speed decrease
- `void rampUpAndDown(Direction direction, unsigned long rampUpMs, unsigned long rampDownMs)` - Sequential ramp up and down

#### Speed Setting
- `void setTargetSpeed(int speed)` - Set target speed (0-255)
- `void setTargetSpeedPercent(int percent)` - Set target speed (0-100%)

#### State Monitoring
- `int getCurrentSpeed() const` - Get current speed (0-255)
- `int getCurrentSpeedPercent() const` - Get current speed percentage
- `Direction getCurrentDirection() const` - Get current direction
- `bool isRamping() const` - Check if ramping in progress
- `bool isMoving() const` - Check if motor is moving

### Direction Enum
- `TomIBT2::CW` - Clockwise rotation
- `TomIBT2::CCW` - Counter-clockwise rotation
- `TomIBT2::UNKNOWN` - Unknown/unset direction

## Examples

The library includes three comprehensive examples:

1. **BasicControl.ino** - Simple motor rotation with status monitoring
2. **RampUpControl.ino** - Advanced ramping with state machine pattern
3. **RampUpAndDown.ino** - Demonstrates sequential ramp-up and ramp-down

## Supported Platforms

- **Arduino**: Uno, Nano, Pro Mini, Mega, Leonardo
- **ESP32**: All variants
- **ESP8266**: NodeMCU, Wemos D1, etc.
- **STM32**: Various boards
- **Teensy**: 3.x and 4.x series
- **Other**: Most Arduino-compatible boards

## Troubleshooting

### Common Issues
- **Motor not responding**: Check wiring and power supply
- **Erratic behavior**: Ensure PWM pins are used for RPWM/LPWM
- **Compilation errors**: Update to latest library version

### Debug Tips
```cpp
// Enable serial debugging
Serial.begin(115200);

// Monitor motor state
Serial.print("Speed: ");
Serial.print(motor.getCurrentSpeed());
Serial.print(" | Direction: ");
Serial.print(motor.getCurrentDirection() == TomIBT2::CW ? "CW" : "CCW");
Serial.print(" | Ramping: ");
Serial.println(motor.isRamping() ? "YES" : "NO");
```

## Documentation

- [Complete API Documentation](docs/api.md)
- [Changelog](CHANGELOG.md)
- [Examples](examples/)

## Contributing

Contributions are welcome! Please feel free to submit pull requests or report issues on GitHub.

## License

This library is released under the MIT License. See [LICENSE](LICENSE) for details.

## Author

**Tom Dhanabhon**
- Email: info@dhanabhon.com
- GitHub: [@Dhanabhon](https://github.com/Dhanabhon)

---

If this library helped your project, please consider giving it a star on GitHub!