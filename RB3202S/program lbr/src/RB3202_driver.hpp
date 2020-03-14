#pragma once
//#include <Arduino.h>

#include "RB3202_DRV8833.hpp"

#define FREGUENCY 5000
#define MAX_PWM 1024

class RB3202_driver: public RB3202_DRV8833
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
    RB3202_driver();

    void motorStartWorking();
    void stop();
    void setMotor();
    void power(float power_0, float power_1);
    void soloPower(float power, bool motor);
    void stop(bool motor);

    ~RB3202_driver();
};