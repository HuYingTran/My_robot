#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"

#include "settings.h"

uint32_t time_start;
uint32_t time_current;

Adafruit_MPU6050 mpu;

SemaphoreHandle_t mpu6050_Mutex;

void mpu6050_init() {
    if (!mpu.begin())
    {
        while (1)
        {
            delay(10);
        }
    }
    // Cấu hình cơ bản (có thể bỏ qua nếu mặc định phù hợp)
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
    time_start = micros();
}

void read_mpu(void *pvParameters) {
    float v, r;
    for (;;) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        v = mpu.a.acceleration.x * (micros() - time_start)^2;
        r = mpu.g.gyro.x * (micros() - time_start);
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE) {
            My_robot.g += r;
            time_start = micros();
            xSemaphoreGive(mpu6050_Mutex);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void task_read_mpu6050() {
    mpu6050_Mutex = xSemaphoreCreateMutex();  // Tạo mutex
    xTaskCreatePinnedToCore(Task1code, "Task1", 4096, NULL, 1, &Task1, 0);
}