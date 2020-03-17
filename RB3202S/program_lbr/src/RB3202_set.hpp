#pragma once

#include <thread>
#include <mutex>
#include <stdio.h>
#include <unistd.h>

#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/periph_ctrl.h"
#include "driver/timer.h"

#include "RB3202_pinout.hpp"

#define LED_R                   0
#define LED_G                   1
#define LED_B                   2

#define SW0                     SW_0_GPIO
#define SW1                     SW_1_GPIO
#define SW2                     SW_2_GPIO
#define SW3                     SW_3_GPIO

#define TIMER_DIVIDER           16
#define TIMER_SCALE             (TIMER_BASE_CLK / TIMER_DIVIDER)
#define TIMER_INTERVAL0_SEC     (3.4179)
#define TIMER_INTERVAL1_SEC     (5.78)
#define TEST_WITHOUT_RELOAD     0
#define TEST_WITH_RELOAD        1

//std::mutex o_led_mx;

class rb_periphery
{
    private:
    volatile bool m_led_state[3][2] = {{0,0}, {0,0}, {0,0}};

    protected:
    void setPinOut();
    void setTimer();
    void peripheriesService(void * pvParameters);

    public:
    bool LEDS(bool state);
    bool ledState( int led, bool state);
    bool ledChange(int led);

    bool readButton(gpio_num_t sw);

    int time(int timer_group = 0);
};