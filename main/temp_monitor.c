#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ds18b20.h"

static const char *TAG = "TEMP_MONITOR";
#define DS18B20_GPIO 4

static void temp_task(void *pvParameters)
{
    (void)pvParameters;

    ESP_LOGI(TAG, "temp_task started on GPIO%d", DS18B20_GPIO);
    ds18b20_init(DS18B20_GPIO);

    while (1) {
        float t = 0.0f;

        if (ds18b20_read_temp_c(DS18B20_GPIO, &t) == DS18B20_OK) {
            ESP_LOGI(TAG, "Temp = %.2f C (placeholder for now)", t);
        } else {
            ESP_LOGE(TAG, "Temp read failed");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "app_main: creating temp_task");

    xTaskCreate(
        temp_task,
        "temp_task",
        4096,
        NULL,
        5,
        NULL
    );
}