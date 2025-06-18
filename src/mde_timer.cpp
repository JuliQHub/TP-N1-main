#include <arduino.h>
#include "timer.h"

uint16_t timer_displays = 0, timer_p1 = 0, timer_p2 = 0, timer_p3 = 0;
void config_TIMER0(void)
{
    TCCR0A = (1 << WGM01);  // Activa el bit CTC (clear timer on compare match)                        // del TCCR0A (timer counter/control register)
    OCR0A = 62;             // valor de comparacion de int cada 1ms
    TCCR0B = (1 << CS02);   // divido por 256 y generar interrupciones cada 1 ms
    TIMSK0 = (1 << OCIE0A); // Habilita las interrupciones entimer compare
}

ISR(TIMER0_COMPA_vect) // Funcion de invocacion del vector de interrupciones (TIMERO en comparacion en nuestro caso)
{
    timer_displays++;

    if (timer_p1 > 0)
    {
        timer_p1--;
    }
    if (timer_p2 > 0)
    {
        timer_p2--;
    }
    if (timer_p3 > 0)
    {
        timer_p3--;
    }
}