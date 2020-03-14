#pragma once

#include "RB3202_pinout.hpp"

#define LED_R 0
#define LED_G 1
#define LED_B 2

#define SW0 SW_0_GPIO
#define SW1 SW_1_GPIO
#define SW2 SW_2_GPIO
#define SW3 SW_3_GPIO

class rb_periphery
{
    private:
    volatile bool m_led_state[3][2] = {{0,0}, {0,0}, {0,0}};
    
    public:
    bool setPeriphery();

    bool LEDS(bool state);
    bool ledState( int led, bool state);
    bool ledChange(int led);

    bool readButton(gpio_num_t sw);

    bool nextThread(bool(*function)(), int repeat, bool micros = false);
};