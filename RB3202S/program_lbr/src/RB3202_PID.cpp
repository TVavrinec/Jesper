#include "RB3202_PID.hpp"
#include "RB3202_encoder.hpp"
#include "RB3202_driver.hpp"
#include "RB3202_pinout.hpp"

std::mutex mx;

RB3202_driver sed;

RB3202_PID::RB3202_PID()
{
    PID();    
}

bool RB3202_PID::PID() 
{
    new std::thread([&]()
    {
        RB3202_encoder encoder0 (RB3202::ENC_B1_GPIO, RB3202::ENC_A1_GPIO);
        RB3202_encoder encoder1 (RB3202::ENC_B2_GPIO, RB3202::ENC_A2_GPIO);
        encoder0.init();
        encoder1.init();
        while(1) 
        {
            for(int a = 0; a<10; a++)
            {
                m_encoder[0] = encoder0.getCount();
                m_encoder[1] = encoder1.getCount();
                rotateVirtualWheels(m_wheel_rps[0], 0);
                rotateVirtualWheels(m_wheel_rps[1], 1);
                setWheelPower(0);
                setWheelPower(1);
                vTaskDelay(10000);
            }
        }
    });
    return true;
}

float RB3202_PID::rotateVirtualWheels(float m_wheel_rps, int wheel)
{
    m_virtual_vheel[wheel] += (m_wheel_rps * COUNT_STEP);
    return m_virtual_vheel[wheel];
}

float RB3202_PID::calcalatePID(int wheel)
{
    float change_power;
    float distanc_position;
    float p_member;
    float d_member;
    
    distanc_position = m_virtual_vheel[wheel] - m_encoder[wheel];
    p_member = distanc_position * m_p;
    d_member = (distanc_position-m_dp_memori[wheel])*m_d;
    
    change_power = d_member + p_member;
    m_dp_memori[wheel] = distanc_position;
    
    return change_power;
}

float RB3202_PID::setWheelPower(int wheel)
{
    float change_power = calcalatePID(wheel);
    if(abs(m_motor_power[wheel] + change_power) <= 120)
    {
        switch (m_driver[wheel])
        {
        case 1:
            m_motor_power[wheel] += change_power;
            sed.soloPower(m_motor_power[wheel], wheel);
            break;
        case 2:
            if(m_plan_position[wheel]>m_encoder[wheel])
            {
                m_motor_power[wheel] += change_power;
                sed.soloPower(m_motor_power[wheel], wheel);
            }
            else
            {
                m_wheel_rps[wheel] = 0;
                sed.soloPower(0, wheel);
                mx.lock();
                m_driver[wheel] = 1;
                mx.unlock();
            }
            break;
        default:
            break;
        }
    }
    return m_motor_power[wheel];
}




void RB3202_PID::off()
{
    mx.lock();
    m_driver[0] = 0;
    m_driver[1] = 0;
    mx.unlock();
}

void RB3202_PID::setRotate(float wheel0, float wheel1)
{
    m_wheel_rps[0] = wheel0;
    m_wheel_rps[1] = wheel1;
    mx.lock();
    m_driver[0] = 1;
    m_driver[1] = 1;
    mx.unlock();
}

void RB3202_PID::wheelRotate(float rotate, bool wheel)
{
    mx.lock();
    m_driver[wheel] = 1;
    mx.unlock();

    m_wheel_rps[wheel] = rotate;
}

float RB3202_PID::readPowerPID(int wheel)
{
    return m_motor_power[wheel];
}

void RB3202_PID::motorGoPosition(int motor, int distance, float cm_per_s, void (*fc)(), int wheel_diametr, int puls_per_rotate)
{
    float circuit = wheel_diametr * PI;

    m_wheel_rps[motor] = cm_per_s/circuit;
    m_plan_position[motor] = m_encoder[motor]+int((distance/circuit) * puls_per_rotate);
    mx.lock();
    m_driver[motor] = 2;
    mx.unlock();
    call_back = fc;
}

bool RB3202_PID::motorGoAnglePosition(int motor, int angle, float speed, int encoder_puls)
{
    m_wheel_rps[motor] = speed;
    m_plan_position[motor] = m_encoder[motor]+int((angle/360) * encoder_puls);
    mx.lock();
    m_driver[motor] = 2;
    mx.unlock();
    return true;
}

bool RB3202_PID::driverState(int wheel)
{
    return m_driver[wheel];
}

RB3202_PID::~RB3202_PID()
{
}