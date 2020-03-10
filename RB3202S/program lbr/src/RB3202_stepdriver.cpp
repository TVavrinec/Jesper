#include "RB3202_stepdriver.hpp"
#include "RB3202_pinout.hpp"

std::mutex o_stepr_mx;

RB3202_stepdriver::RB3202_stepdriver()
{

}

bool RB3202_stepdriver::countPWM()
{
    new std::thread([&]()
    {
        while(1) 
        {

        }
    });
}

bool RB3202_stepdriver::setRotate(float step_per_second)
{
    o_stepr_mx.lock();
    m_speed = step_per_second;
    o_stepr_mx.unlock();

    return 1;
}