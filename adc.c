/* 心拍数計からとった電圧値をSPI経由で取得するプログラム郡 */
//定数定義
#include "mylib.h"
#include "library.h"

static unsigned char *buff; //送受信用バッファ
static int adc_value;

static const double V_REF = 3.3;

int adc_init(void)
{

    pinMode(SPI_SS_PORT, OUTPUT); //22pinを出力に設定
    digitalWrite(SPI_SS_PORT, 1); //SS信号初期化
    *buff = 0x0; //バッファ初期化

    return 0;
}

int adc_get_value(int ch)
{
    //mcp3204用
    *buff = 0b00000110; //送信用データをバッファにセット(先頭5bitはダミー)
    /* digitalWrite(SPI_SS_PORT, 0); //SS信号をLOW出力にして通信開始 */
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */

    *buff = 0b00000000; //送信用データをバッファにセット(後方6bitはダミー)
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */
    adc_value = ((*buff&0xF) << 8);

    *buff = 0; //送信用データをバッファにセット(ダミー)
    /* wiringPiSPIDataRW(ch, buff, 1); //データ送受信 */
    /* digitalWrite(SPI_SS_PORT, 1); //SS信号をHIGH出力にして通信終了 */
    adc_value += *buff;   
 
    printf ("ch  :\traw,\tvoltege\n");
    printf ("ch0 :\t%4d,\t%3.2lf\n", adc_value, adc_value*V_REF/4096);

    return 0;
}
