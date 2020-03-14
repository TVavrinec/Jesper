#pragma once

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

#define ESP_LEDC_CHANNEL 16

namespace pwm
{
    bool configTimer(gpio_num_t pin, ledc_timer_t channel, ledc_mode_t mode, int frequency, ledc_timer_bit_t resolution);
};