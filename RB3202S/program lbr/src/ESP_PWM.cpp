#include "ESP_PWM.hpp"

bool pwm::configTimer(gpio_num_t pin,ledc_channel_t channel , ledc_timer_t timer, ledc_mode_t mode, int frequency, ledc_timer_bit_t resolution)
{
    ledc_timer_config_t pwm_timer;
    ledc_channel_config_t pwm_channel;

    pwm_timer.duty_resolution = resolution;
    pwm_timer.freq_hz = frequency;
    pwm_timer.speed_mode = mode;
    pwm_timer.timer_num = timer;

    pwm_channel.channel = channel;
    pwm_channel.duty = 0;
    pwm_channel.gpio_num = pin;
    pwm_channel.hpoint = 0;
    pwm_channel.speed_mode = mode;
    pwm_channel.timer_sel = timer;

    ledc_timer_config(&pwm_timer);
    ledc_channel_config(&pwm_channel);
    ledc_set_duty(mode, channel, 0);

    return 1;
}