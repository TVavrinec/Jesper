#include "RB3202_stepdriver.hpp"
#include "RB3202_pinout.hpp"

std::mutex o_stepr_mx;

rb_stepdriver::rb_stepdriver()
{
}

void rb_stepdriver::calcalateStep()
{

}



bool rb_stepdriver::setMotor()
{
    //setAllMotorPins();
    calcalateStep();

    return 1;
}

bool rb_stepdriver::setRotate(float m_step_per_second)
{
    m_micro_step_period = 10000/m_step_per_second;
    return 1;
}