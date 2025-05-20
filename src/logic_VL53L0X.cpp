#include "Adafruit_VL53L0X.h"
#include <SimpleKalmanFilter.h>

TaskHandle_t TaskReadVL53L0X;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Cấu hình Kalman filter (noise tham khảo, có thể tinh chỉnh)
SimpleKalmanFilter vl53l0x_KalmanFilter(1, 1, 0.01);

void vl53l0x_init()
{
    if (!lox.begin())
    {
        Serial.println(F("Failed to boot VL53L0X"));
        while (1) {
            delay(10);
        }
    }
    // start continuous ranging
    lox.startRangeContinuous();
}

void task_vl53l0x(void *pvParameters)
{
    while(1) {
        if (lox.isRangeComplete())
        {
            float rawDistance = lox.readRange();
            float filteredDistance = vl53l0x_KalmanFilter.updateEstimate(rawDistance);
            Serial.println(filteredDistance);
            vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }
}

void task_read_vl53l0x()
{
    xTaskCreatePinnedToCore(
        task_vl53l0x,     // Hàm task
        "ReadVL53L0X",    // Tên task
        4096,             // Stack size
        NULL,             // Tham số
        1,                // Ưu tiên
        &TaskReadVL53L0X, // Handle task
        1                 // Core 1 (có thể để 0 hoặc 1 tùy)
    );
}