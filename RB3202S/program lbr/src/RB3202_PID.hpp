#pragma once

#include <mutex>
#include <Arduino.h>
#include <thread>


#define COUNT_STEP 0.8

class RB3202_PID
{
private:
    int32_t m_encoder[2];

    volatile float m_wheel_rps[2] = {0,0};
    volatile float m_virtual_vheel[2] = {0,0};

    volatile float m_dp_memori[2] = {0,0}; // Distanc_Position_memori
    volatile float m_motor_power[2] = {0,0};

    volatile int m_plan_position[2];
    volatile int m_driver[2] = {0, 0};

    volatile float m_p = 0.01;
    volatile float m_d = 5;

    hw_timer_t * timer = NULL;

    bool PID();

    void (*call_back)();

    float rotateVirtualWheels(float wheel_rpm, int wheel);
    float calcalatePID(int wheel);
    float setWheelPower(int wheel);

public:
    RB3202_PID();

    void off();

    void setRotate(float wheel0, float wheel1);
    void wheelRotate(float rotate, bool wheel);

    void motorGoPosition(int motor, int distance, float cm_per_s, void (*callBack)() = nullptr, int wheel_diametr = 69, int puls_per_rotate = 480);
    bool motorGoAnglePosition(int motor, int angle, float rotate_per_second, int encoder_puls = 480);

    bool driverState(int wheel);

    float readPowerPID(int wheel);

    ~RB3202_PID();
};