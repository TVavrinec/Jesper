#include <Arduino.h>

class RB3202_driver
{
private:
    void setMotorPwmPins(gpio_num_t pin, uint8_t channel);
    void setAllMotorPins();
    
    void goForward(bool motor, float pwm);
    void goBack(bool motor, float pwm);
    void setPwm(bool motor, bool direction, float pwm);
    
    int pwmPercent(float percent);

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