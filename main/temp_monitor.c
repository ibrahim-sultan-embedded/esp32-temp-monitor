#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "TEMP_MONITOR";

typedef struct {
    int temp_c;
    uint32_t ts_ms;
} temp_msg_t;

static QueueHandle_t temp_queue;

static void sensor_task(void *pv)
{
    (void)pv;
    int temp = 25;

    while (1) {
        temp_msg_t msg = {
            .temp_c = ++temp,
            .ts_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS),
        };

        xQueueSend(temp_queue, &msg, portMAX_DELAY);
        ESP_LOGI(TAG, "Sensor sent: %dC at %lu ms", msg.temp_c, (unsigned long)msg.ts_ms);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void logger_task(void *pv)
{
    (void)pv;
    temp_msg_t msg;

    while (1) {
        if (xQueueReceive(temp_queue, &msg, portMAX_DELAY)) {
            ESP_LOGI(TAG, "Logger received: %dC (ts=%lu ms)", msg.temp_c, (unsigned long)msg.ts_ms);
        }
    }
}

void app_main(void)
{
    ESP_LOGI(TAG, "Boot OK. Creating queue + tasks...");

    temp_queue = xQueueCreate(8, sizeof(temp_msg_t));
    if (!temp_queue) {
        ESP_LOGE(TAG, "Failed to create queue");
        return;
    }

    xTaskCreate(sensor_task, "sensor_task", 4096, NULL, 5, NULL);
    xTaskCreate(logger_task, "logger_task", 4096, NULL, 5, NULL);
}