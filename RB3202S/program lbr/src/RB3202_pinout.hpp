#pragma once

#include <stdio.h>

#include <driver/adc.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/ledc.h"
#include "esp_err.h"

namespace RB3202
{
    static const gpio_num_t BOARD_OFF_GPIO = GPIO_NUM_13;
    static const gpio_num_t BOARD_BATREF_GPIO = GPIO_NUM_35;

    static const gpio_num_t MOTOR_PWM0_GPIO = GPIO_NUM_0;
    static const gpio_num_t MOTOR_PWM1_GPIO = GPIO_NUM_16;
    static const gpio_num_t MOTOR_PWM2_GPIO = GPIO_NUM_5;
    static const gpio_num_t MOTOR_PWM3_GPIO = GPIO_NUM_17;
    static const gpio_num_t MOTOR_SLEEP_GPIO = GPIO_NUM_2;

    static const gpio_num_t ENC_A1_GPIO = GPIO_NUM_15;
    static const gpio_num_t ENC_B1_GPIO = GPIO_NUM_4;
    static const gpio_num_t ENC_A2_GPIO = GPIO_NUM_19;
    static const gpio_num_t ENC_B2_GPIO = GPIO_NUM_18;

    static const gpio_num_t SW_0_GPIO = GPIO_NUM_25;
    static const gpio_num_t SW_1_GPIO = GPIO_NUM_12;
    static const gpio_num_t SW_2_GPIO = GPIO_NUM_27;
    static const gpio_num_t SW_3_GPIO = GPIO_NUM_26;

    static const gpio_num_t LED_R_GPIO = GPIO_NUM_21;
    static const gpio_num_t LED_G_GPIO = GPIO_NUM_36;
    static const gpio_num_t LED_B_GPIO = GPIO_NUM_39;

    static const gpio_num_t SERVO_SMART_GPIO = GPIO_NUM_23;
};