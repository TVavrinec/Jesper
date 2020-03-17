#include "RB3202_pinout.hpp"
#include "RB3202_DRV8833.hpp"

void RB3202_DRV8833::setMotorPwmPins(gpio_num_t pin, uint8_t channel)
{
    ledc_timer_config_t pwm_timer;
    ledc_channel_config_t pwm_channel;

    pwm_timer.duty_resolution = PWM_RESOLUTION;
    pwm_timer.freq_hz = FREGUENCY;
    pwm_timer.speed_mode = LEDC_HIGH_SPEED_MODE;
    pwm_timer.timer_num = ledc_timer_t(channel);

    pwm_channel.channel = ledc_channel_t(channel);
    pwm_channel.duty = 0;
    pwm_channel.gpio_num = pin;
    pwm_channel.hpoint = 0;
    pwm_channel.speed_mode = LEDC_HIGH_SPEED_MODE;
    pwm_channel.timer_sel = ledc_timer_t(channel);

    ledc_timer_config(&pwm_timer);
    ledc_channel_config(&pwm_channel);
    ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(channel), 0);
}

void RB3202_DRV8833::setAllMotorPins()
{
    gpio_set_direction(RB3202::MOTOR_SLEEP_GPIO, GPIO_MODE_INPUT);
    gpio_set_level(RB3202::MOTOR_SLEEP_GPIO, 0);

    setMotorPwmPins(RB3202::MOTOR_PWM0_GPIO, 0);
    setMotorPwmPins(RB3202::MOTOR_PWM1_GPIO, 1);
    setMotorPwmPins(RB3202::MOTOR_PWM2_GPIO, 2);
    setMotorPwmPins(RB3202::MOTOR_PWM3_GPIO, 3);
}

int RB3202_DRV8833::pwmPercent(float percent)
{
    return MAX_PWM - int((percent*0.01)*MAX_PWM);
}

void RB3202_DRV8833::goForward(bool motor, float pwm)
{
    if(motor)
    {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(2), MAX_PWM);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(3), pwmPercent(pwm));
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(2));
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(3));
    }
    else
    {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(0), MAX_PWM);
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(1), pwmPercent(pwm));
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(1));
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(2));
    }
}

void RB3202_DRV8833::goBack(bool motor, float pwm)
{
    if(motor)
    {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(2), pwmPercent(pwm));
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(3), MAX_PWM);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(2));
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(3));
    }
    else
    {
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(0), pwmPercent(pwm));
        ledc_set_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(1), MAX_PWM);
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(1));
        ledc_update_duty(LEDC_HIGH_SPEED_MODE, ledc_channel_t(2));
    } 
}

void RB3202_DRV8833::setPwm(bool motor, bool direction, float pwm)
{
    if(direction)
        goForward(motor,pwm);
    else
        goBack(motor, pwm);
}

void RB3202_DRV8833::deactivateSleepMode()
{
    gpio_set_level(RB3202::MOTOR_SLEEP_GPIO, 1);
}

void RB3202_DRV8833::activateSleepMode()
{
    gpio_set_level(RB3202::MOTOR_SLEEP_GPIO, 0);
}