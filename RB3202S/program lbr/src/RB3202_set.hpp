#pragma once

#include "RB3202_pinout.hpp"

#define LED_R 0
#define LED_G 1
#define LED_B 2

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