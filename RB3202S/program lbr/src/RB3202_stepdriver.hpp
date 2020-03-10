#pragma once

#include <mutex>
#include <Arduino.h>
#include <functional>
#include <thread>

class RB3202_stepdriver
{
    private:
    float m_speed;
    float sin;

    bool setPWM();
    bool countPWM();

    public:
    RB3202_stepdriver();

    bool setRotate(float step_per_second);

};