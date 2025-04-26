#ifndef _espAFMotor_h_
#define _espAFMotor_h_

#include <Arduino.h>

// Pin PWM
#define PIN_PWM1 33
#define PIN_PWM2 13
#define PIN_PWM3 27
#define PIN_PWM4 14

// Bit positions in the 74HCT595 shift register output
#define MOTOR1_A 2
#define MOTOR1_B 3
#define MOTOR2_A 1
#define MOTOR2_B 4
#define MOTOR4_A 0
#define MOTOR4_B 6
#define MOTOR3_A 5
#define MOTOR3_B 7

// Constants for motor direction
#define FORWARD 1
#define BACKWARD 2
#define BRAKE 3
#define RELEASE 4

// 74HCT595 latch control pins
#define MOTORLATCH 32
#define MOTORCLK 12
#define MOTORENABLE 26
#define MOTORDATA 25

#define RESOLUTION 8
#define DC_MOTOR_PWM_RATE 5000

class AFMotorController
{
public:
    AFMotorController(void);
    void enable(void);
    void latch_tx(void);
    uint8_t TimerInitalized;
};

class AF_DCMotor
{
public:
    AF_DCMotor(uint8_t motornum, uint16_t freq = DC_MOTOR_PWM_RATE);
    void run(uint8_t cmd);
    void setSpeed(uint8_t speed);

private:
    uint8_t motornum;
    uint16_t pwmfreq;
};

#endif
