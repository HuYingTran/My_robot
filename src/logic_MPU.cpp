#include "Adafruit_MPU6050.h"
#include "Adafruit_Sensor.h"
#include "Wire.h"

#include "settings.h"

uint32_t time_start;
uint32_t time_current;

Adafruit_MPU6050 mpu;

SemaphoreHandle_t mpu6050_Mutex;

// Khởi tạo handle cho task
TaskHandle_t TaskReadMPU;

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

// Hàm task đọc MPU6050
void TaskMPU6050(void *pvParameters)
{
    // Biến lưu dữ liệu đọc được
    sensors_event_t accel, gyro, temp;
    while (1)
    {
        // Đọc dữ liệu
        mpu.getEvent(&accel, &gyro, &temp);
        // In dữ liệu đọc được
        Serial.print("[ACC] X: ");
        Serial.print(accel.acceleration.x);
        Serial.print(", Y: ");
        Serial.print(accel.acceleration.y);
        Serial.print(", Z: ");
        Serial.println(accel.acceleration.z);

        Serial.print("[GYRO] X: ");
        Serial.print(gyro.gyro.x);
        Serial.print(", Y: ");
        Serial.print(gyro.gyro.y);
        Serial.print(", Z: ");
        Serial.println(gyro.gyro.z);

        Serial.print("[TEMP] ");
        Serial.print(temp.temperature);
        Serial.println(" C");

        Serial.println("------");

        // Delay 500ms
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void task_read_mpu6050() {
    mpu6050_Mutex = xSemaphoreCreateMutex();  // Tạo mutex
    xTaskCreatePinnedToCore(
        TaskMPU6050,   // Hàm task
        "ReadMPU6050", // Tên task
        4096,          // Stack size
        NULL,          // Tham số
        1,             // Ưu tiên
        &TaskReadMPU,  // Handle task
        1              // Core 1 (có thể để 0 hoặc 1 tùy)
    );

}