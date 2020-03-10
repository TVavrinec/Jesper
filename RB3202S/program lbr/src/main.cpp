#include "RB3202_lbr.hpp"

void setup()
{
  ui.set_periphery(); // nazacatku musime inicializovat uzivatelske rozhrani (tlacitka a ledky)
  ui.led_state(LED_R, HIGH);  // rozsvitime cervenou jako vychozi stav semaforu
  ui.LEDS(HIGH);
  delay(1000);
}

void loop()
{
  ui.LEDS(LOW);
  /*if(ui.read_button(SW0))  // pokud stiskneme tlacitko SW1 zacneme prepinat semafor
  {
    ui.led_state(LED_R, HIGH);
    Serial.println("1");
  }*/
  if(ui.read_button(SW1))  // pokud stiskneme tlacitko SW1 zacneme prepinat semafor
  {
    ui.led_state(LED_R, HIGH);
    Serial.println("1");
  }
  else if(ui.read_button(SW2))  // pokud stiskneme tlacitko SW1 zacneme prepinat semafor
  {
    ui.led_state(LED_G, HIGH);
    Serial.println("1");
  }
  else if(ui.read_button(SW3))  // pokud stiskneme tlacitko SW1 zacneme prepinat semafor
  {
    ui.led_state(LED_B, HIGH);
    Serial.println("1");
  }
  delay(100);   // protoze nemusime cist tlacitka a nastoavoval ledky az tak casto chvili pockame
}