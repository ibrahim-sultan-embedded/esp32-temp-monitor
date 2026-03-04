#pragma once
#include <stdint.h>

typedef enum {
    DS18B20_OK = 0,
    DS18B20_ERR = -1
} ds18b20_status_t;

ds18b20_status_t ds18b20_init(int gpio_num);
ds18b20_status_t ds18b20_read_temp_c(int gpio_num, float *out_temp_c);