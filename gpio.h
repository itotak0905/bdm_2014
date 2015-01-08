#ifndef MY_GPIO_H
#define MY_GPIO_H

#define FCLED_R_PIN 22
#define FCLED_B_PIN 17
#define FCLED_G_PIN 27 

#define RLED_PIN 21

#define ON 1
#define OFF 0

#define RED 0
#define BLUE 1
#define GREEN 2
#define FCLED_COLOR_NUM 3

typedef struct _fcled
{
    int color;
    int duty;
    int data;
}fcled_t;

typedef struct _led
{
    int duty;
    int data;
}led_t;

int all_led_init(void);

int fcled_set_color(int new_color);

int fcled_set_duty(int new_duty);

int rled_set_duty(int new_duty);

int fcled_set_data(int new_data);

int rled_set_data(int new_data);

int fcled_status_update(void);

int rled_status_update(void);

int all_led_status_update(void);

#endif
