#include "RB3202_lbr.hpp"

int timer[2] = {0,0};

extern "C" void app_main()
{
  ui.userInterface();
  while(true)
  {
    while (timer[0] < timer[1])
    {
      timer[0] = ui.time(1);
    }
    timer[1] = timer[0]+1000;
    gpio_set_level(RB3202::LED_R_GPIO, 0);
    while (timer[0] < timer[1])
    {
      timer[0] = ui.time(1);
    }
    timer[1] = timer[0]+1000;
    gpio_set_level(RB3202::LED_R_GPIO, 1);
  }
}