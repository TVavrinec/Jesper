#include "RB3202_pinout.hpp"
#include "RB3202_DRV8833.hpp"

void RB3202_DRV8833::setMotorPwmPins(gpio_num_t pin, uint8_t channel)
{
    ledcSetup(channel,FREGUENCY,10);
    ledcWrite(channel,MAX_PWM);
    ledcAttachPin(pin,channel);
}

void RB3202_DRV8833::setAllMotorPins()
{
    pinMode(RB3202::MOTOR_SLEEP_GPIO,OUTPUT);
    digitalWrite(RB3202::MOTOR_SLEEP_GPIO, LOW);

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
        ledcWrite(2,MAX_PWM);
        ledcWrite(3,pwmPercent(pwm));  
    }
    else
    {
        ledcWrite(0,MAX_PWM);
        ledcWrite(1,pwmPercent(pwm));
    }
}

void RB3202_DRV8833::goBack(bool motor, float pwm)
{
    if(motor)
    {
        ledcWrite(2,pwmPercent(pwm));
        ledcWrite(3,MAX_PWM);
    }
    else
    {
        ledcWrite(0,pwmPercent(pwm));
        ledcWrite(1,MAX_PWM);
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
    digitalWrite(RB3202::MOTOR_SLEEP_GPIO, HIGH);
}

void RB3202_DRV8833::activateSleepMode()
{
    digitalWrite(RB3202::MOTOR_SLEEP_GPIO, LOW);
}