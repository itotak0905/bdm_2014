#ifndef MY_ADC_H
#define MY_ADC_H

#define SPI_SS_PORT 8 //GPIO 8
#define SPI_CHANNEL 0 //SPIチャンネル

#define V_REF 3.3


int adc_init(void);

int adc_get_value(int ch);

int free_buff(void);

#endif
