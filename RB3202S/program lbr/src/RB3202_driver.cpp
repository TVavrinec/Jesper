#include "RB3202_pinout.hpp"
#include "RB3202_driver.hpp"

RB3202_driver::RB3202_driver()
{
    setMotor();
}

void RB3202_driver::setMotorPwmPins(gpio_num_t pin, uint8_t channel)
{
    ledcSetup(channel,FREGUENCY,10);
    ledcWrite(channel,MAX_PWM);
    ledcAttachPin(pin,channel);
}

void RB3202_driver::setAllMotorPins()
{
    pinMode(RB3202::MOTOR_SLEEP_GPIO,OUTPUT);
    digitalWrite(RB3202::MOTOR_SLEEP_GPIO, LOW);

    setMotorPwmPins(RB3202::MOTOR_PWM0_GPIO, 0);
    setMotorPwmPins(RB3202::MOTOR_PWM1_GPIO, 1);
    setMotorPwmPins(RB3202::MOTOR_PWM2_GPIO, 2);
    setMotorPwmPins(RB3202::MOTOR_PWM3_GPIO, 3);
}

int RB3202_driver::pwmPercent(float percent)
{
    return MAX_PWM - int((percent*0.01)*MAX_PWM);
}

void RB3202_driver::goForward(bool motor, float pwm)
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

void RB3202_driver::goBack(bool motor, float pwm)
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

void RB3202_driver::setPwm(bool motor, bool direction, float pwm)
{
    if(direction)
        goForward(motor,pwm);
    else
        goBack(motor, pwm);
}













void RB3202_driver::motorStartWorking()
{
    digitalWrite(RB3202::MOTOR_SLEEP_GPIO,HIGH);
}

void RB3202_driver::setMotor()
{
    setAllMotorPins();
    motorStartWorking();
}

void RB3202_driver::power(float power_0, float power_1)
{
    if(power_1 > 0)
        setPwm(1, 1, abs(power_1));
    else
        setPwm(1, 0, abs(power_1));

    if(power_0 > 0)
        setPwm(0, 1, abs(power_0));
    else
        setPwm(0, 0, abs(power_0));
}

void RB3202_driver::soloPower(float power, bool motor)
{
    if(power > 100)
        power = 100;
    else if (power < -100)
        power = -100;
    
    if(power > 0)
        setPwm(motor, 1, abs(power));
    else
        setPwm(motor, 0, abs(power));
}

void RB3202_driver::stop()
{
    digitalWrite(RB3202::MOTOR_SLEEP_GPIO, LOW);
}

RB3202_driver::~RB3202_driver()
{
}