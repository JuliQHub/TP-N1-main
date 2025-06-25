#include <arduino.h>
#include "multiplexado.h"
#include "timer.h"

#define TIEMPO_DISPLAY 5

uint16_t unidad, decena, centena, unidad_de_mil, minutos_display, segundos_display, segundos_ct;
extern bool flag_p3;
extern uint16_t timer_cuenta_regresiva, timer_parpadeo_total, timer_parpadeo;
bool estado_cuenta_regresiva = 0, flag_parpadeo = 0;

enum DISPLAYS
{
    DISPLAY_1,
    DISPLAY_2,
    DISPLAY_3,
    DISPLAY_4
};

void mde_multiplexado(void)
{
    extern uint16_t timer_displays;
    uint8_t Tabla_Digitos_7seg[10] = {0x3f, 0x06, 0x5B, 0x4f, 0x66, 0x6D, 0x7C, 0x07, 0x7f, 0x67};

    static enum DISPLAYS estado_displays = DISPLAY_1;

    switch (estado_displays)
    {
    case DISPLAY_1:
        entero_4dig();
        if (timer_displays > TIEMPO_DISPLAY)
        {
            if (unidad_de_mil > 2)
            {
                unidad_de_mil = 2;
            }
            PORTD &= (0b00000011);
            PORTB &= (0b11000000);

            PORTB |= (Tabla_Digitos_7seg[unidad_de_mil] >> 4);
            PORTD |= (Tabla_Digitos_7seg[unidad_de_mil] << 4);
            PORTD |= (1 << PD2);
            estado_displays = DISPLAY_2;
            timer_displays = 0;
        }
        break;

    case DISPLAY_2:
        entero_4dig();
        if (timer_displays > TIEMPO_DISPLAY)
        {
            PORTD &= (0b00000011);
            PORTB &= (0b11000000);

            PORTB |= (Tabla_Digitos_7seg[centena] >> 4);
            PORTD |= (Tabla_Digitos_7seg[centena] << 4);
            PORTB |= (1 << PB3);
            PORTD |= (1 << PD3);

            estado_displays = DISPLAY_3;
            timer_displays = 0;
        }
        break;

    case DISPLAY_3:
        entero_4dig();
        if (timer_displays > TIEMPO_DISPLAY)
        {
            if (decena > 6)
            {
                decena = 6;
            }
            PORTD &= (0b00000011);
            PORTB &= (0b11000000);

            PORTB |= (Tabla_Digitos_7seg[decena] >> 4);
            PORTD |= (Tabla_Digitos_7seg[decena] << 4);
            PORTB |= (1 << PB4);

            estado_displays = DISPLAY_4;
            timer_displays = 0;
        }
        break;
    case DISPLAY_4:
        entero_4dig();
        if (timer_displays > TIEMPO_DISPLAY)
        {
            PORTD &= (0b00000011);
            PORTB &= (0b11000000);

            PORTB |= (Tabla_Digitos_7seg[unidad] >> 4);
            PORTD |= (Tabla_Digitos_7seg[unidad] << 4);
            PORTB |= (1 << PB5);

            estado_displays = DISPLAY_1;
            timer_displays = 0;
        }
        break;
    }
}
void minutos_segundos_display(void)
{
    segundos_display = segundos_ct % 60;
    minutos_display = segundos_ct / 60;
}
void entero_4dig(void)
{
    minutos_segundos_display();
    uint16_t num = minutos_display * 100 + segundos_display;
    unidad = num % 10;
    num /= 10;
    decena = num % 10;
    num /= 10;
    centena = num % 10;
    unidad_de_mil = num / 10;
}

void cuenta_regresiva(void)
{
    if (flag_p3 == 1)
    {

        flag_p3 = 0;
        estado_cuenta_regresiva = !estado_cuenta_regresiva;
        timer_cuenta_regresiva = 0;
    }
    if (estado_cuenta_regresiva == 1)
    {
        if (timer_cuenta_regresiva == 1000)
        {
            if (segundos_ct > 0)
            {
                segundos_ct--;
                timer_cuenta_regresiva = 0;
            }
            else
            {
                flag_parpadeo = 1;
            }
        }
    }
}

void parpadeo(void)
{
    if (flag_parpadeo == 1)
    {
        if (timer_parpadeo_total <= 10000)
        {
            if (flag_parpadeo == 0)
            {
                {
                    if (timer_parpadeo <= 500)
                    {
                        DDRD &= (0b11110000);
                        DDRB &= (0b00000111);
                    }
                    else
                    {
                        flag_parpadeo = 1;
                    }
                    if (flag_parpadeo == 1)
                    {
                        if (timer_parpadeo <= 500)
                        {
                            DDRD |= (0b11110000);
                            DDRB |= (0b00000111);
                        }
                        else
                        {
                            flag_parpadeo = 0;
                        }
                    }
                }
            }
        }
    }
}
