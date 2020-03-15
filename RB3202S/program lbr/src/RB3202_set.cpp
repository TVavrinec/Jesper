//#include <Arduino.h>
#include <thread>
#include <mutex>
#include "RB3202_set.hpp"

std::mutex o_led_mx;

bool rb_periphery::setPeriphery()
{
    Serial.begin(115200);

    gpio_set_direction(RB3202::LED_R_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(RB3202::LED_G_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(RB3202::LED_B_GPIO, GPIO_MODE_OUTPUT);
    
    gpio_set_level(RB3202::LED_R_GPIO, LOW);
    gpio_set_level(RB3202::LED_G_GPIO, LOW);
    gpio_set_level(RB3202::LED_B_GPIO, LOW);


    gpio_set_direction(RB3202::SW_0_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(RB3202::SW_1_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(RB3202::SW_2_GPIO, GPIO_MODE_INPUT);
    gpio_set_direction(RB3202::SW_3_GPIO, GPIO_MODE_INPUT);

    gpio_pullup_en(RB3202::SW_0_GPIO);
    gpio_pullup_en(RB3202::SW_1_GPIO);
    gpio_pullup_en(RB3202::SW_2_GPIO);
    gpio_pullup_en(RB3202::SW_3_GPIO);


    new std::thread([&]()
    {
        while(true)
        {
            gpio_set_level(RB3202::LED_R_GPIO, m_led_state[0][0]);
            gpio_set_level(RB3202::LED_G_GPIO, m_led_state[1][0]);
            gpio_set_level(RB3202::LED_B_GPIO, m_led_state[2][0]);

            while((m_led_state[0][0] == m_led_state[0][1])
                &&(m_led_state[1][0] == m_led_state[1][1])
                &&(m_led_state[2][0] == m_led_state[2][1]))
            {
                usleep(10000);
            }
            o_led_mx.lock();
            m_led_state[0][1] = m_led_state[0][0];
            m_led_state[1][1] = m_led_state[1][0];
            m_led_state[2][1] = m_led_state[2][0];
            o_led_mx.unlock();
        }
    });

    return true;
};

bool rb_periphery::LEDS(bool state)
{
    o_led_mx.lock();
    m_led_state[0][0] = state;
    m_led_state[1][0] = state;
    m_led_state[2][0] = state;
    o_led_mx.unlock();

    return true;
};

bool rb_periphery::ledState(int led, bool state)
{
    o_led_mx.lock();
    m_led_state[led][0] = state;
    o_led_mx.unlock();

    return true;
}

bool rb_periphery::ledChange(int led)
{
    o_led_mx.lock();
    m_led_state[led][0] = !m_led_state[led][0];
    o_led_mx.unlock();

    return true;
}


bool rb_periphery::readButton(gpio_num_t sw)
{
    return !gpio_get_level(sw);
}



bool rb_periphery::nextThread( bool (*function)(), int repeat, bool micros)
{
    if(!micros)
    {
        repeat *= 1000;
    }
    new std::thread([&]()
    {
        while(function())
        {
            usleep(repeat);
        }
    });
    return true;
}
