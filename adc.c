/* 心拍数計からとった電圧値をSPI経由で取得するプログラム郡 */
//定数定義
#include "mylib.h"
#include "library.h"

#define SS_PORT 22 //GPIO 22
#define SPI_CHANNEL 0 //SPIチャンネル

int speed = 10000000; //通信速度(Hz)
unsigned char *buff; //送受信用バッファ
int adc_value;

int adc_init(void)
{
/*     if((wiringPiSPISetup (SPI_CHANNEL, speed)) < 0){ //SPIチャンネル初期化 */
/* printf("wiringPiSPISetup error \n"); */
/* return -1 ; */
/*     } */

/*     if(wiringPiSetupGpio() == -1){ //GPIO初期化 */
/* printf("wiringPiSetupGpio error\n"); */
/* return -1; */
/*     } */
/*     pinMode(SS_PORT, OUTPUT); //22pinを出力に設定 */
/*     digitalWrite(SS_PORT, 1); //SS信号初期化 */
    *buff = 0x0; //バッファ初期化

    return 0;
}

int adc_get_value(int ch)
{
    //mcp3204用
    *buff = 0b00000110; //送信用データをバッファにセット(先頭5bitはダミー)
    /* digitalWrite(SS_PORT, 0); //SS信号をLOW出力にして通信開始 */
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */

    *buff = 0b00000000; //送信用データをバッファにセット(後方6bitはダミー)
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */
    adc_value = ((*buff&0xF) << 8);

    *buff = 0; //送信用データをバッファにセット(ダミー)
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */
    /* digitalWrite(SS_PORT, 1); //SS信号をHIGH出力にして通信終了 */
    adc_value += *buff;   
 
    printf ("ch  :\traw,\tvoltege\n");
    printf ("ch0 :\t%4d,\t%3.2lf\n", adc_value, adc_value*5.0/4096);
}
