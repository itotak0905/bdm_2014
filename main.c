#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();

    printf("test\n");

    rled_set_data(ON);
    all_led_status_update();
    usleep(500000);
    rled_set_data(OFF);
    all_led_status_update();
    usleep(500000);
    
    free_buff();

    return 0;
}
