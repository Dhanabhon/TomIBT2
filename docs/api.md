# TomIBT2 Library

## Methods

### `begin()`

#### Syntax

```c
motor.begin();
```

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {}
```

#### See also

* [begin()](#begin)


### `rampUp()`

Ramp from the current speed to full speed with a linear transition

#### Syntax

```c
motor.rampUp(direction, timoutMs);
```

#### Parameters

* direction: a variable of motor rotation direction controlling
* timeoutMs: the value to ramping timeout in milliseconds

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {
    motor.rampUp(TomIBT2::CW, 2000);
    ...
}
```

#### See also

*[rampUp()](#rampup)

### `rampDown()`

Ramp from the current speed to full stop with a linear transition

#### Syntax

```c
motor.rampDown(timoutMs);
```

#### Parameter

* timeoutMs: the value to ramping timeout in milliseconds

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {
    ...
    motor.rampDown(2000);
    ...
}
```

#### See also

*[rampDown()](#rampdown)


### `rotate()`

Rotate the motor by setting the target speed of the motor

#### Syntax

```c
motor.rotate(speed, direction);
```

#### Parameters

* speed: the value from 0 - 255 to set the target speed of the motor
* direction: a variable of motor rotation direction controlling

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {
    motor.rotate(255, TomIBT2::CW);
}
```

#### See also

*[rotate()](#rotate)

### `setTargetSpeed()`

Control the speed of the motor by value from 0 - 255

#### Syntax

```c
motor.setTargetSpeed(speed);
```

#### Parameter

* speed: the value from 0 - 255 to set the target speed of the motor

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {
    motor.setTargetSpeed(255);
    motor.rampUp(TomIBT2::CW, 2000);
}
```

#### See also

*[setTargetSpeed()](#settargetspeed)

### `setTargetSpeedPercent()`

Control the speed percentage of the motor by value from 0 - 100. This is essentially the same as `setTargetSpeed()` but with a smaller input scale.

#### Syntax

```c
motor.setTargetSpeedPercent(percent);
```

#### Parameter

* percent: the value from 0 - 100 to set the target speed of the motor

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  motor.begin();
}

void loop() {
    motor.setTargetSpeedPercent(80);
    motor.rampUp(TomIBT2::CW, 2000);
}
```

#### See also

*[setTargetSpeedPercent()](#settargetspeedpercent)

### `getCurrentSpeed()`

Get the value of motor speed currently.

#### Syntax

```c
motor.getCurrentSpeed();
```

#### Return

Returns an integer from 0 - 255 for the current motor speed.

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  Serial.begin(115200);

  motor.begin();
}

void loop() {
    motor.setTargetSpeed(100);
    motor.rampUp(TomIBT2::CW, 2000);

    Serial.println(motor.getCurrentSpeed());
}
```

#### See also

*[getCurrentSpeed()](#getcurrentspeed)

### `getCurrentSpeedPercent()`

Get the percent of motor speed currently.

#### Syntax

```c
motor.getCurrentSpeedPercent();
```

#### Return

Returns an integer from 0 - 100 for the current motor speed.

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  Serial.begin(115200);

  motor.begin();
}

void loop() {
    motor.setTargetSpeed(100);
    motor.rampUp(TomIBT2::CW, 2000);

    Serial.println(motor.getCurrentSpeedPercent());
}
```

#### See also

*[getCurrentSpeedPercent()](#getcurrentspeedpercent)

### `getCurrentDirection()`

Get the direction of motor speed currently.

#### Syntax

```c
motor.getCurrentDirection();
```

#### Return

Returns a clockwise (CW) or counter clockwise (CCW) for the current motor direction.

#### Example

```c
#include <TomIBT2.h>

#define MOTOR_PIN_R_EN        7
#define MOTOR_PIN_L_EN        8
#define MOTOR_PIN_RPWM        10
#define MOTOR_PIN_LPWM        9

TomIBT2 motor(MOTOR_PIN_R_EN, MOTOR_PIN_L_EN, MOTOR_PIN_RPWM, MOTOR_PIN_LPWM);

void setup() {
  Serial.begin(115200);

  motor.begin();
}

void loop() {
    motor.setTargetSpeed(100);
    motor.rampUp(TomIBT2::CW, 2000);

    switch(motor.getCurrentSpeedPercent()) {
        case TomIBT2::CW: {
            Serial.println("CW");
            break;
        }
        case TomIBT2::CCW: {
            Serial.println("CW");
            break;
        }
    }
}
```

#### See also

*[getCurrentDirection()](#getcurrentdirection)
