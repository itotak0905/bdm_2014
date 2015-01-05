#ifndef MY_GPIO_H
#define MY_GPIO_H

typedef struct _led
{
    int color;
    int duty;
    int mode;
}led_t;

int led_set_color(int new_color);

int led_set_duty(int new_duty);

int led_set_mode(int new_mode);

int led_status_update(void);

#endif
