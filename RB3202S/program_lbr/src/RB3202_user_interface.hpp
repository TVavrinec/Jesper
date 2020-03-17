#pragma once

#include "RB3202_pinout.hpp"
#include "RB3202_set.hpp"

class rb_user_interface: public rb_periphery
{
public:
    void userInterface();
    //bool nextThread(bool(*function)(), int repeat, bool micros = false);
};