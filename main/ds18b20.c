#include "ds18b20.h"

ds18b20_status_t ds18b20_init(int gpio_num)
{
    (void)gpio_num;
    return DS18B20_OK;
}

ds18b20_status_t ds18b20_read_temp_c(int gpio_num, float *out_temp_c)
{
    (void)gpio_num;
    if (!out_temp_c) return DS18B20_ERR;
    *out_temp_c = 0.0f; // placeholder until hardware arrives
    return DS18B20_OK;
}