#include "RB3202_lbr.hpp"


void setup()
{
  ui.setPeriphery();
  Serial.begin(115200);

  RB3202_stepdriver steper;
  steper.setMotor();
  steper.setRotate(10);
  //RB3202_stepdriver stepr;
  //stepr.setMotor();
  //stepr.setRotate(20);
}

void loop()
{
  delay(1000);
}