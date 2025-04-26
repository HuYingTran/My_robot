#include "Arduino.h"
#include "espAFMotor.h"

static uint8_t latch_state;

AFMotorController::AFMotorController(void)
{
    TimerInitalized = false;
}

void AFMotorController::enable(void)
{
    pinMode(MOTORLATCH, OUTPUT);
    pinMode(MOTORENABLE, OUTPUT);
    pinMode(MOTORDATA, OUTPUT);
    pinMode(MOTORCLK, OUTPUT);

    latch_state = 0;

    latch_tx(); // "reset"
    digitalWrite(MOTORENABLE, LOW);
}

void AFMotorController::latch_tx(void)
{
    digitalWrite(MOTORLATCH, LOW);
    shiftOut(MOTORDATA, MOTORCLK, MSBFIRST, latch_state);
    digitalWrite(MOTORLATCH, HIGH);
}

static AFMotorController MC;

// ----- PWM INIT -----

#define RESOLUTION 8

inline void initPWM(uint8_t pin, uint8_t freq, uint8_t channel)
{
    ledcDetachPin(pin);
    ledcSetup(channel, freq, RESOLUTION);
    ledcAttachPin(pin, channel);
}

inline void setPWM(uint8_t channel, uint8_t speed)
{
    ledcWrite(channel, speed);
}

AF_DCMotor::AF_DCMotor(uint8_t num, uint16_t freq)
{
    motornum = num;
    pwmfreq = freq;

    MC.enable();

    switch (num)
    {
    case 1:
        latch_state &= ~_BV(MOTOR1_A) & ~_BV(MOTOR1_B);
        MC.latch_tx();
        initPWM(PIN_PWM1, freq, 1);
        break;
    case 2:
        latch_state &= ~_BV(MOTOR2_A) & ~_BV(MOTOR2_B);
        MC.latch_tx();
        initPWM(PIN_PWM2, freq, 2);
        break;
    case 3:
        latch_state &= ~_BV(MOTOR3_A) & ~_BV(MOTOR3_B);
        MC.latch_tx();
        initPWM(PIN_PWM3, freq, 3);
        break;
    case 4:
        latch_state &= ~_BV(MOTOR4_A) & ~_BV(MOTOR4_B);
        MC.latch_tx();
        initPWM(PIN_PWM4, freq, 4);
        break;
    }
}

void AF_DCMotor::run(uint8_t cmd)
{
    uint8_t a, b;
    switch (motornum)
    {
    case 1:
        a = MOTOR1_A;
        b = MOTOR1_B;
        break;
    case 2:
        a = MOTOR2_A;
        b = MOTOR2_B;
        break;
    case 3:
        a = MOTOR3_A;
        b = MOTOR3_B;
        break;
    case 4:
        a = MOTOR4_A;
        b = MOTOR4_B;
        break;
    default:
        return;
    }

    switch (cmd)
    {
    case FORWARD:
        latch_state |= _BV(a);
        latch_state &= ~_BV(b);
        break;
    case BACKWARD:
        latch_state &= ~_BV(a);
        latch_state |= _BV(b);
        break;
    case RELEASE:
        latch_state &= ~_BV(a);
        latch_state &= ~_BV(b);
        break;
    }
    MC.latch_tx();
}

void AF_DCMotor::setSpeed(uint8_t speed)
{
    switch (motornum)
    {
    case 1:
        setPWM(1, speed);
        break;
    case 2:
        setPWM(2, speed);
        break;
    case 3:
        setPWM(3, speed);
        break;
    case 4:
        setPWM(4, speed);
        break;
    }
}