# TomIBT2 Library API Reference

**Version 1.2.0** - Enhanced Arduino library for IBT-2 H-Bridge motor driver control

## Constructor

### `TomIBT2()`

Initialize motor driver with pin assignments.

#### Syntax

```c
TomIBT2 motor(r_en_pin, l_en_pin, rpwm_pin, lpwm_pin);
```

#### Parameters

* **r_en_pin**: Forward drive enable pin (HIGH = enable, LOW = disable)
* **l_en_pin**: Reverse drive enable pin (HIGH = enable, LOW = disable)
* **rpwm_pin**: Forward PWM signal pin (must be PWM capable)
* **lpwm_pin**: Reverse PWM signal pin (must be PWM capable)

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_R_EN    7
#define MOTOR_L_EN    8
#define MOTOR_RPWM    10  // PWM pin
#define MOTOR_LPWM    9   // PWM pin

TomIBT2 motor(MOTOR_R_EN, MOTOR_L_EN, MOTOR_RPWM, MOTOR_LPWM);
```

---

## Initialization Methods

### `begin()`

Initialize motor driver pins and set initial state. Includes pin validation and ensures motor is stopped initially.

#### Syntax

```c
motor.begin();
```

#### Example

```c
void setup() {
  motor.begin();
}
```

#### See also

* [Constructor](#tomibt2)

---

## Motor Control Methods

### `rotate()`

Immediately rotate motor at specified speed and direction. Stops any ongoing ramping operations.

#### Syntax

```c
motor.rotate(speed, direction);
```

#### Parameters

* **speed**: Motor speed (0-255, automatically clamped to valid range)
* **direction**: Motor rotation direction (`TomIBT2::CW` or `TomIBT2::CCW`)

#### Example

```c
void loop() {
  // Rotate clockwise at full speed
  motor.rotate(255, TomIBT2::CW);
  delay(2000);

  // Rotate counter-clockwise at half speed
  motor.rotate(128, TomIBT2::CCW);
  delay(2000);
}
```

#### See also

* [stop()](#stop)
* [brake()](#brake)

### `stop()`

Stop motor by disabling drive circuits (allows coasting to a stop).

#### Syntax

```c
motor.stop();
```

#### Example

```c
void loop() {
  motor.rotate(200, TomIBT2::CW);
  delay(3000);

  motor.stop();  // Coast to stop
  delay(2000);
}
```

#### See also

* [brake()](#brake)
* [rotate()](#rotate)

### `brake()`

Stop motor with active braking action (immediate stop with motor resistance).

#### Syntax

```c
motor.brake();
```

#### Example

```c
void loop() {
  motor.rotate(200, TomIBT2::CW);
  delay(3000);

  motor.brake();  // Active braking
  delay(2000);
}
```

#### See also

* [stop()](#stop)
* [rotate()](#rotate)

---

## Ramping Control Methods

### `rampUp()`

Gradually increase motor speed from current speed to target speed with linear transition.

#### Syntax

```c
motor.rampUp(direction, timeoutMs);
```

#### Parameters

* **direction**: Motor rotation direction (`TomIBT2::CW` or `TomIBT2::CCW`)
* **timeoutMs**: Time in milliseconds for complete ramp-up to target speed

#### Example

```c
void setup() {
  motor.begin();
  motor.setTargetSpeedPercent(80);  // Set target to 80%
}

void loop() {
  motor.rampUp(TomIBT2::CW, 2000);  // Ramp up over 2 seconds

  if (!motor.isRamping()) {
    // Ramping complete
    delay(1000);
  }
}
```

#### See also

* [rampDown()](#rampdown)
* [setTargetSpeed()](#settargetspeed)
* [isRamping()](#isramping)

### `rampDown()`

Gradually decrease motor speed from current speed to zero with linear transition.

#### Syntax

```c
motor.rampDown(timeoutMs);
```

#### Parameters

* **timeoutMs**: Time in milliseconds for complete ramp-down to stop

#### Example

```c
void loop() {
  // After motor is running
  motor.rampDown(1500);  // Ramp down over 1.5 seconds

  if (!motor.isRamping() && !motor.isMoving()) {
    // Motor completely stopped
    delay(2000);
  }
}
```

#### See also

* [rampUp()](#rampup)
* [isRamping()](#isramping)
* [isMoving()](#ismoving)

### `rampUpAndDown()`

Automatically perform sequential ramp-up to target speed followed by ramp-down to stop.

#### Syntax

```c
motor.rampUpAndDown(direction, rampUpMs, rampDownMs);
```

#### Parameters

* **direction**: Motor rotation direction (`TomIBT2::CW` or `TomIBT2::CCW`)
* **rampUpMs**: Time in milliseconds for ramp-up phase
* **rampDownMs**: Time in milliseconds for ramp-down phase

#### Example

```c
void setup() {
  motor.begin();
  motor.setTargetSpeedPercent(75);  // Set target to 75%
}

void loop() {
  motor.rampUpAndDown(TomIBT2::CW, 3000, 2000);  // 3s up, 2s down

  if (!motor.isRamping() && !motor.isMoving()) {
    delay(2000);  // Pause between cycles
  }
}
```

#### See also

* [rampUp()](#rampup)
* [rampDown()](#rampdown)
* [setTargetSpeed()](#settargetspeed)

---

## Speed Setting Methods

### `setTargetSpeed()`

Set target speed for ramping operations using absolute values.

#### Syntax

```c
motor.setTargetSpeed(speed);
```

#### Parameters

* **speed**: Target speed (0-255, automatically clamped to valid range)

#### Example

```c
void setup() {
  motor.begin();
  motor.setTargetSpeed(200);  // Set target to 200/255
}

void loop() {
  motor.rampUp(TomIBT2::CW, 2000);
}
```

#### See also

* [setTargetSpeedPercent()](#settargetspeedpercent)
* [rampUp()](#rampup)

### `setTargetSpeedPercent()`

Set target speed for ramping operations using percentage values.

#### Syntax

```c
motor.setTargetSpeedPercent(percent);
```

#### Parameters

* **percent**: Target speed percentage (0-100, automatically clamped)

#### Example

```c
void setup() {
  motor.begin();
  motor.setTargetSpeedPercent(80);  // Set target to 80%
}

void loop() {
  motor.rampUp(TomIBT2::CW, 2000);
}
```

#### See also

* [setTargetSpeed()](#settargetspeed)
* [getCurrentSpeedPercent()](#getcurrentspeedpercent)

---

## State Monitoring Methods

### `getCurrentSpeed()`

Get current motor speed as absolute value.

#### Syntax

```c
int speed = motor.getCurrentSpeed();
```

#### Returns

Integer from 0-255 representing current motor speed.

#### Example

```c
void loop() {
  motor.rotate(150, TomIBT2::CW);

  int currentSpeed = motor.getCurrentSpeed();
  Serial.print("Current speed: ");
  Serial.println(currentSpeed);  // Will print 150
}
```

#### See also

* [getCurrentSpeedPercent()](#getcurrentspeedpercent)
* [isMoving()](#ismoving)

### `getCurrentSpeedPercent()`

Get current motor speed as percentage value.

#### Syntax

```c
int percent = motor.getCurrentSpeedPercent();
```

#### Returns

Integer from 0-100 representing current motor speed percentage.

#### Example

```c
void loop() {
  motor.rotate(128, TomIBT2::CW);

  int speedPercent = motor.getCurrentSpeedPercent();
  Serial.print("Speed: ");
  Serial.print(speedPercent);
  Serial.println("%");  // Will print approximately 50%
}
```

#### See also

* [getCurrentSpeed()](#getcurrentspeed)
* [setTargetSpeedPercent()](#settargetspeedpercent)

### `getCurrentDirection()`

Get current motor rotation direction.

#### Syntax

```c
TomIBT2::Direction direction = motor.getCurrentDirection();
```

#### Returns

Direction enum value:
* `TomIBT2::CW` - Clockwise rotation
* `TomIBT2::CCW` - Counter-clockwise rotation
* `TomIBT2::UNKNOWN` - Unknown/unset direction

#### Example

```c
void loop() {
  motor.rotate(200, TomIBT2::CW);

  switch(motor.getCurrentDirection()) {
    case TomIBT2::CW:
      Serial.println("Rotating clockwise");
      break;
    case TomIBT2::CCW:
      Serial.println("Rotating counter-clockwise");
      break;
    case TomIBT2::UNKNOWN:
      Serial.println("Direction unknown");
      break;
  }
}
```

#### See also

* [rotate()](#rotate)
* [isMoving()](#ismoving)

### `isRamping()`

Check if motor is currently performing a ramping operation (either up or down).

#### Syntax

```c
bool ramping = motor.isRamping();
```

#### Returns

* `true` if ramping operation is in progress
* `false` if no ramping operation is active

#### Example

```c
void loop() {
  motor.rampUp(TomIBT2::CW, 2000);

  if (motor.isRamping()) {
    Serial.println("Motor is ramping...");
  } else {
    Serial.println("Ramping complete");
  }
}
```

#### See also

* [rampUp()](#rampup)
* [rampDown()](#rampdown)
* [isMoving()](#ismoving)

### `isMoving()`

Check if motor is currently moving (speed greater than zero).

#### Syntax

```c
bool moving = motor.isMoving();
```

#### Returns

* `true` if motor speed is greater than 0
* `false` if motor is stopped

#### Example

```c
void loop() {
  if (motor.isMoving()) {
    Serial.print("Motor running at ");
    Serial.print(motor.getCurrentSpeedPercent());
    Serial.println("%");
  } else {
    Serial.println("Motor stopped");
  }

  delay(500);
}
```

#### See also

* [getCurrentSpeed()](#getcurrentspeed)
* [isRamping()](#isramping)
* [stop()](#stop)

---

## Direction Constants

### Direction Enumeration

```c
enum Direction {
  CW = 1,     // Clockwise rotation
  CCW = 2,    // Counter-clockwise rotation
  UNKNOWN = 3 // Unknown/unset direction
};
```

#### Usage

```c
motor.rotate(255, TomIBT2::CW);     // Clockwise
motor.rotate(128, TomIBT2::CCW);    // Counter-clockwise
```

---

## Complete Example

```c
#include <TomIBT2.h>

#define MOTOR_R_EN    7
#define MOTOR_L_EN    8
#define MOTOR_RPWM    10
#define MOTOR_LPWM    9

TomIBT2 motor(MOTOR_R_EN, MOTOR_L_EN, MOTOR_RPWM, MOTOR_LPWM);

void setup() {
  Serial.begin(115200);
  motor.begin();
  motor.setTargetSpeedPercent(80);
}

void loop() {
  // Ramp up
  Serial.println("Ramping up...");
  motor.rampUp(TomIBT2::CW, 2000);

  while (motor.isRamping()) {
    Serial.print("Speed: ");
    Serial.print(motor.getCurrentSpeedPercent());
    Serial.println("%");
    delay(100);
  }

  // Run at full speed
  Serial.println("Running at target speed");
  delay(2000);

  // Ramp down
  Serial.println("Ramping down...");
  motor.rampDown(1500);

  while (motor.isRamping()) {
    Serial.print("Speed: ");
    Serial.print(motor.getCurrentSpeedPercent());
    Serial.println("%");
    delay(100);
  }

  // Pause
  Serial.println("Cycle complete, pausing...");
  delay(2000);
}
```

---

## Version History

### v1.2.0 (2025)
- Fixed `rampUpAndDown()` function implementation
- Added `isRamping()` and `isMoving()` state monitoring methods
- Enhanced ramping algorithms with improved timing
- Added comprehensive input validation
- Improved const correctness for getter methods