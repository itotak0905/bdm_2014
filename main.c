#include "library.h"
#include "mylib.h"

#define BUF_SIZE 2048

int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();
    
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    printf("test\n");

    
    int value, counter, state;
    state = counter = 0;
    for (;;) {
	value = adc_get_value(0);
	printf("%d\n",value);
	if (value > 600) {
	    if (counter <= 3) {
		counter++;
	    }
	    if (counter == 4) 
		rled_set_data(ON);
	} else {
	    if (counter >= 1) {
		counter--;
	    }
	    if (counter == 0) {
		rled_set_data(OFF);
	    }
	}
	
	all_led_status_update();
	usleep(10000);
    }
    free_buff();

    return 0;
}
