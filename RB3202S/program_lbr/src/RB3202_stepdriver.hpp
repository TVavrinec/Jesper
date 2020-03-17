#pragma once

#include <mutex>
#include <functional>
#include <thread>

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#include "RB3202_driver.hpp"

#define MICRO_STEP          256
#define PERIOD_MICRO_STEP   0.062831853

class rb_stepdriver: public RB3202_DRV8833
{
    private:
    double m_wheel_position;
    int m_micro_step_period;

    void calcalateStep();

    public:
    rb_stepdriver();

    bool setMotor();
    bool setRotate(float step_per_second);
};