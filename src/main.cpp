#include <Arduino.h>
#include "multiplexado.h"
#include "timer.h"
#include "botones.h"

int main(void)
{
  DDRD |= (0b11111100);
  DDRB |= (0b00111111);
  DDRC &= (0b11000111);
  PORTC |= (0b00111000);

  config_TIMER0();
  sei();
  while (1)
  {
    mde_multiplexado();
    mde_pulsadores();
    cuenta_regresiva();
    parpadeo();
  }

  return 0;
}