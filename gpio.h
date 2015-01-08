#ifndef MY_GPIO_H
#define MY_GPIO_H

#define LED_R_PIN 22
#define LED_B_PIN 17
#define LED_G_PIN 27 

#define ON 1
#define OFF 0

#define RED 0
#define BLUE 1
#define GREEN 2
#define LED_COLOR_NUM 3

typedef struct _led
{
    int color;
    int duty;
    int data;
}led_t;

int led_init(void);

int led_set_color(int new_color);

int led_set_duty(int new_duty);

int led_set_data(int new_data);

int led_status_update(void);

#endif
