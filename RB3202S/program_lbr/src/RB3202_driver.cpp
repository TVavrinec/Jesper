#include "RB3202_pinout.hpp"
#include "RB3202_driver.hpp"

RB3202_driver::RB3202_driver()
{
    setMotor();
}



void RB3202_driver::motorStartWorking()
{
    gpio_set_level(RB3202::MOTOR_SLEEP_GPIO, 1);
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
    gpio_set_level(RB3202::MOTOR_SLEEP_GPIO, 0);
}

RB3202_driver::~RB3202_driver()
{
}