#include "library.h"
#include "mylib.h"

static int spi_speed = 10000; //通信速度(Hz)

int all_init(void)
{
    // Initialize WiringPi
    if(wiringPiSetupGpio() == -1) {
	printf("wiringPiSPISetup error \n");
	return 1 ;
    }
    //SPIチャンネル初期化
    if((wiringPiSPISetup (SPI_CHANNEL, spi_speed)) < 0){ 
	printf("wiringPiSPISetup error \n");
	return 1 ;
    }

    all_led_init();
    adc_init();
    sound_init();

    return 0;
}
