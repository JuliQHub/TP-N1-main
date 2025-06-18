#include <Arduino.h>
#include "botones.h"
#include "timer.h"

#define up 0
#define falling 1
#define down 2
#define raising 3

volatile bool flag_p1 = 0, flag_p2 = 0, flag_p3 = 0;
extern uint16_t timer_p1, timer_p2, timer_p3, segundos_ct;

void mde_pulsadores(void)
{
    static uint8_t estado_p1 = up, estado_p2 = up, estado_p3 = up;

    switch (estado_p1)
    {
    case up:
        if (((PINC >> PC5) & 1) == 0)
        {
            estado_p1 = falling;
            timer_p1 = 20;
        }
        break;
    case falling:
        if (((PINC >> PC5) & 1) == 1)
        {
            estado_p1 = up;
            timer_p1 = 0;
        }
        if ((((PINC >> PC5) & 1) == 0) && timer_p1 == 0)
        {
            estado_p1 = down;
            flag_p1 = 1;
            if (segundos_ct < 1200)
            {
                segundos_ct++;
            }
        }
        break;
    case down:
        if (((PINC >> PC5) & 1) == 1)
        {
            estado_p1 = raising;
            timer_p1 = 20;
        }
        break;
    case raising:
        if (((PINC >> PC5) & 1) == 0)
        {
            estado_p1 = down;
        }
        if (((PINC >> PC5) & 1) == 1 && timer_p1 == 0)
        {
            estado_p1 = up;
            timer_p1 = 0;
        }
        break;
    default:
        estado_p1 = up;
    }
    switch (estado_p2)
    {
    case up:
        if (((PINC >> PC4) & 1) == 0)
        {
            estado_p2 = falling;
            timer_p2 = 20;
        }
        break;
    case falling:
        if (((PINC >> PC4) & 1) == 1)
        {
            estado_p2 = up;
            timer_p2 = 0;
        }
        if ((((PINC >> PC4) & 1) == 0) && timer_p2 == 0)
        {
            estado_p2 = down;
            flag_p2 = 1;
            if (segundos_ct > 0)
            {
                segundos_ct--;
            }
        }
        break;
    case down:
        if (((PINC >> PC4) & 1) == 1)
        {
            estado_p2 = raising;
            timer_p2 = 20;
        }
        break;
    case raising:
        if (((PINC >> PC4) & 1) == 0)
        {
            estado_p2 = down;
        }
        if (((PINC >> PC4) & 1) == 1 && timer_p2 == 0)
        {
            estado_p2 = up;
            timer_p2 = 0;
        }
        break;
    default:
        estado_p2 = up;
    }

    switch (estado_p3)
    {
    case up:
        if (((PINC >> PC3) & 1) == 0)
        {
            estado_p3 = falling;
            timer_p3 = 20;
        }
        break;
    case falling:
        if (((PINC >> PC3) & 1) == 1)
        {
            estado_p3 = up;
            timer_p3 = 0;
        }
        if ((((PINC >> PC3) & 1) == 0) && timer_p3 == 0)
        {
            estado_p3 = down;
            flag_p3 = 1;
        }
        break;
    case down:
        if (((PINC >> PC3) & 1) == 1)
        {
            estado_p3 = raising;
            timer_p3 = 20;
        }
        break;
    case raising:
        if (((PINC >> PC3) & 1) == 0)
        {
            estado_p3 = down;
        }
        if (((PINC >> PC3) & 1) == 1 && timer_p3 == 0)
        {
            estado_p3 = up;
            timer_p3 = 0;
        }
        break;
    default:
        estado_p3 = up;
    }
}