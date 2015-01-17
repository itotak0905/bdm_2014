#include "library.h"
#include "mylib.h"

#define BUF_SIZE 2048

//#define BDM_OUTPUT
//#define BDM_BRAIN
#define BDM_HEART

//出力系
#ifdef BDM_OUTPUT
int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();
    
    struct sockaddr_in addr;
    char buf[BUF_SIZE];

    printf("test output\n");
    while(1){
	
	all_led_status_update();
	usleep(1*1000);
    }
    
    free_buff();

    return 0;
}
#endif

//脳波系
#ifdef BDM_BRAIN 
int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();
    
    struct sockaddr_in addr;
    char buf[BUF_SIZE];
    printf("test brain\n");

    int fd = serial_open();
    listen_loop(fd);
    serial_close(fd);


    while(1){
	
    }
    
    free_buff();

    return 0;
}
#endif

//心拍系
#ifdef BDM_HEART
int main(void)
{
    /* init周りゴニョゴニョ */
    all_init();
    
    struct sockaddr_in addr;
    char buf[BUF_SIZE];
    
    printf("#test heart\n");
    printf("#sec(ms) value\n");
#define SPAN 150
    int i,value[SPAN],sec=0,total=0;
    for (i=0;i<SPAN;i++) value[i]=0;
    while(1){
	total -= value[sec%SPAN];
	value[sec%SPAN] = adc_get_value(0);
	total += value[sec%SPAN];
	printf("%5d %d %4.1f ",sec,value[sec%SPAN], total*1.0/SPAN);
	if (value[sec%SPAN] >  total*1.0/SPAN) {
	    printf("O\n");
	} else {
	    printf("\n");
	}
	sec++;
	usleep(1*1000); /* 1ms */
    }
    
    free_buff();

    return 0;
}
#endif
