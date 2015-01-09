#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();

    printf("test\n");

    int i = 0, j = 0;
    int value_r = 0,value_g = 0,value_b = 0;
    fcled_set_data(ON);
    for (;;) {
	if (j % 100 == 0) {
	    if (i > 0 && i < 100) value_r++; 
	    if (i > 100 && i < 200) value_g++; 
	    if (i > 200 && i < 300) value_b++; 
	    if (i > 300 && i < 400) value_r--; 
	    if (i > 400 && i < 500) value_g--; 
	    if (i > 500 && i < 600) value_b--;
	    if (i == 600) i = 0;
	    fcled_set_color_value(RED, value_r);
	    fcled_set_color_value(GREEN, value_g);
	    fcled_set_color_value(BLUE, value_b);
	    i++;
	    printf("i:%d r:%d g:%d b:%d\n", i, value_r, value_g, value_b);
	}
	j++;
	all_led_status_update();
	usleep(100);
    }
    
    free_buff();

    return 0;
}
