#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();

    printf("test\n");

    
    int i;
    int value;
    printf ("ch  :\traw,\tvoltege\tcount\n");
    for (;;) {
	value = adc_get_value(0);
	printf ("ch0 :\t%4d,\t%3.2lf\t%d\n", value, value*V_REF/4096, i);
	if (value >= 500) { 
	    rled_set_data(ON);
	} else {
	    rled_set_data(OFF);
	}
	all_led_status_update();
	usleep(10000);
    }
    
    free_buff();

    return 0;
}
