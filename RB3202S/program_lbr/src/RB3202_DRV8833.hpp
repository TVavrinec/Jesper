#pragma once

#include "RB3202_pinout.hpp"

#define FREGUENCY               5
#define PWM_RESOLUTION          LEDC_TIMER_10_BIT
#define MAX_PWM                 1023

class RB3202_DRV8833
{
private:
    void setMotorPwmPins(gpio_num_t pin, uint8_t channel);

    void goForward(bool motor, float pwm);
    void goBack(bool motor, float pwm);
    int pwmPercent(float percent);

protected:
    void setAllMotorPins();

    void setPwm(bool motor, bool direction, float pwm);
public:
    void activateSleepMode();
    void deactivateSleepMode();
};