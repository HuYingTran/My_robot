#include "espAFMotor.h"
#include "function.h"

AF_DCMotor motor1(1); // Bánh trước bên trái
AF_DCMotor motor2(2); // Bánh trước bên phải
AF_DCMotor motor3(3); // Bánh sau bên trái
AF_DCMotor motor4(4); // Bánh sau bên phải

void motor_setup()
{
    // Cấu hình tốc độ cho mỗi động cơ
    motor1.setSpeed(150);
    motor2.setSpeed(150);
    motor3.setSpeed(150);
    motor4.setSpeed(150);
}

void motor_set_peed(uint8_t s1, uint8_t s2, uint8_t s3, uint4_t s4)
{
    motor1.setSpeed(s1);
    motor2.setSpeed(s2);
    motor3.setSpeed(s3);
    motor4.setSpeed(s4);
}

// Hàm điều khiển tiến
void moveForward()
{
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
}

// Hàm điều khiển lùi
void moveBackward()
{
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
}

// Hàm điều khiển dịch sang trái
void moveLeft()
{
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
}

// Hàm điều khiển dịch sang phải
void moveRight()
{
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
}

// Hàm điều khiển xoay trái
void rotateLeft()
{
    motor1.run(BACKWARD);
    motor2.run(FORWARD);
    motor3.run(BACKWARD);
    motor4.run(FORWARD);
}

// Hàm điều khiển xoay phải
void rotateRight()
{
    motor1.run(FORWARD);
    motor2.run(BACKWARD);
    motor3.run(FORWARD);
    motor4.run(BACKWARD);
}

// Hàm dừng động cơ
void motor_stop()
{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
}

void moveForward_calib()
{
    if (My_robot.g > ERR_CALIB) {
        motor_set_peed(uint8_t s1, uint8_t s2, uint8_t s3, uint4_t s4)
    } else if (My_robot.g < - ERR_CALIB) {
        motor_set_peed(uint8_t s1, uint8_t s2, uint8_t s3, uint4_t s4)
    } else {
        moveForward();
    }
}