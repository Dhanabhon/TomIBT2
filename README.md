# TomIBT2

TomIBT2 is an Arduino library for controlling the IBT-2 (H-Bridge) motor driver board.

### IBT-2 H-Bridge Usage
#### Usage 1:
- VCC pick MCU 5V power supply, GND connected microcontroller GND
- R_EN and L_EN shorted and connected to 5 level, the drive to work.
- L_PWM, input PWM signal or high motor forward
- R_PWM, input PWM signal or high motor reversal

#### Usage 2:
- VCC pick MCU 5V power supply, GND connected microcontroller GND
- R_EN and L_EN short circuit and PWM signal input connected to high-speed
- L_PWM, pin input 5V level motor is transferred
- R_PWM, pin input 5V level motor reversal
