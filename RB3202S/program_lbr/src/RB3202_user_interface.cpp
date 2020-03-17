#include "RB3202_user_interface.hpp"

void rb_user_interface::userInterface()
{
    setPinOut();
    setTimer();
    TaskHandle_t xHandle = NULL;
    static uint8_t taskParam;
    rb_periphery rbp;
    xTaskCreate( rbp.peripheriesService, "periphService", 10, &taskParam, 1, &xHandle);
}