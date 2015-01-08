#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    led_init();
    /* adc_init(); */
    /* sound_init(); */

    printf("test\n");

    led_set_color(RED);
    led_set_data(ON);
    led_status_update();
    usleep(500000);
    led_set_data(OFF);
    led_status_update();
    usleep(500000);

    led_set_color(GREEN);
    led_set_data(ON);
    led_status_update();
    usleep(500000);
    led_set_data(OFF);
    led_status_update();
    usleep(500000);

    led_set_color(BLUE);
    led_set_data(ON);
    led_status_update();
    usleep(500000);
    led_set_data(OFF);
    led_status_update();
    usleep(500000);
    
    return 0;
}
