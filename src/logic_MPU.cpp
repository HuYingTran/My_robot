#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"

Adafruit_MPU6050 mpu;

void mpu6050_init() {
    if (!mpu.begin())
    {
        while (1)
        {
            delay(10);
        }
    }
}