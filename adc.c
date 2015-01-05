/* 心拍数計からとった電圧値をSPI経由で取得するプログラム郡 */
//定数定義
#include "mylib.h"
#include "library.h"

#define SS_PORT 22 //GPIO 22
#define SPI_CHANNEL 0 //SPIチャンネル

int speed = 10000000; //通信速度(Hz)
unsigned char *buff; //送受信用バッファ


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
/*     *buff = 0x0; //バッファ初期化 */

    return 0;
}

int adc_get_value(int ch)
{
    /* *buff = 0x24; //送信用データをバッファにセット */
    /* digitalWrite(SS_PORT, 0); //SS信号をLOW出力にして通信開始 */
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */
    /* digitalWrite(SS_PORT, 1); //SS信号をHIGH出力にして通信終了 */

    printf("0x%x\n", *buff); //受信データを出力

}
