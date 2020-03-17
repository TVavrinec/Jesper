#include "RB3202_set.hpp"

void rb_periphery::peripheriesService(void * pvParameters)
{
    while(true)
    {
        if( !((m_led_state[0][0] == m_led_state[0][1])
            &&(m_led_state[1][0] == m_led_state[1][1])
            &&(m_led_state[2][0] == m_led_state[2][1])))
        {
            gpio_set_level(RB3202::LED_R_GPIO, m_led_state[0][0]);
            gpio_set_level(RB3202::LED_G_GPIO, m_led_state[1][0]);
            gpio_set_level(RB3202::LED_B_GPIO, m_led_state[2][0]);

            m_led_state[0][1] = m_led_state[0][0];
            m_led_state[1][1] = m_led_state[1][0];
            m_led_state[2][1] = m_led_state[2][0];
        }
        vTaskDelay(1000000);
    }
}

void rb_periphery::setTimer()
{
    timer_start(TIMER_GROUP_0, timer_idx_t(1));
}

void rb_periphery::setPinOut()
{
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

    gpio_set_pull_mode(RB3202::SW_0_GPIO, gpio_pull_mode_t(0));
    gpio_set_pull_mode(RB3202::SW_1_GPIO, gpio_pull_mode_t(0));
    gpio_set_pull_mode(RB3202::SW_2_GPIO, gpio_pull_mode_t(0));
    gpio_set_pull_mode(RB3202::SW_3_GPIO, gpio_pull_mode_t(0));
}

int rb_periphery::time(int timer_group)
{
    uint64_t timer;
    timer_get_counter_value(timer_group_t(int(timer_group/2)),timer_idx_t(timer_group),&timer);
    return timer;
}

bool rb_periphery::LEDS(bool state)
{
    m_led_state[0][0] = state;
    m_led_state[1][0] = state;
    m_led_state[2][0] = state;

    return true;
};

bool rb_periphery::ledState(int led, bool state)
{
    m_led_state[led][0] = state;
    return true;
}

bool rb_periphery::ledChange(int led)
{
    m_led_state[led][0] = !m_led_state[led][0];
    return true;
}


bool rb_periphery::readButton(gpio_num_t sw)
{
    return !gpio_get_level(sw);
}