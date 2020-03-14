#include "RB3202_stepdriver.hpp"
#include "RB3202_pinout.hpp"

std::mutex o_stepr_mx;

RB3202_stepdriver::RB3202_stepdriver()
{
}

void RB3202_stepdriver::calcalateStep()
{
    TaskHandle_t xHandle = NULL;

    // Create the task without using any dynamic memory allocation.
    xHandle = xTaskCreateStatic(
                  vTaskCode,       // Function that implements the task.
                  "NAME",          // Text name for the task.
                  STACK_SIZE,      // Stack size in bytes, not words.
                  ( void * ) 1,    // Parameter passed into the task.
                  tskIDLE_PRIORITY,// Priority at which the task is created.
                  xStack,          // Array to use as the task's stack.
                  &xTaskBuffer );  // Variable to hold the task's data structure.

    // puxStackBuffer and pxTaskBuffer were not NULL, so the task will have
    // been created, and xHandle will be the task's handle.  Use the handle
    // to suspend the task.
    vTaskSuspend( xHandle );

            m_wheel_position += PERIOD_MICRO_STEP;
            usleep(m_micro_step_period);
            Serial.println(m_wheel_position);
}



bool RB3202_stepdriver::setMotor()
{
    //setAllMotorPins();
    calcalateStep();
}

bool RB3202_stepdriver::setRotate(float m_step_per_second)
{
    m_micro_step_period = 10000/m_step_per_second;
    return 1;
}