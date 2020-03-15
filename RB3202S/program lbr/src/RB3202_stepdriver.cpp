#include "RB3202_stepdriver.hpp"
#include "RB3202_pinout.hpp"

std::mutex o_stepr_mx;

RB3202_stepdriver::RB3202_stepdriver()
{
}

void RB3202_stepdriver::calcalateStep()
{

}



bool RB3202_stepdriver::setMotor()
{
    //setAllMotorPins();
    calcalateStep();

    return 1;
}

bool RB3202_stepdriver::setRotate(float m_step_per_second)
{
    m_micro_step_period = 10000/m_step_per_second;
    return 1;
}