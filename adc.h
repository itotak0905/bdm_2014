#ifndef MY_ADC_H
#define MY_ADC_H

#define SPI_SS_PORT 24 //GPIO 24
#define SPI_CHANNEL 0 //SPIチャンネル

int adc_init(void);

int adc_get_value(int ch);

#endif
