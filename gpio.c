/* GPIOでの入出力に関連する関数群 */

/* と思ったけど外部のライブラリ(とりあえずwiringPi)があるのでそっちを使う */
/* と思ったけどbdmに合わせてもう少し使いやすい関数を作る */
#include "mylib.h"
#include "library.h"

static led_t led_status;

int led_init(void)
{ 
    // Initialize WiringPi
    if(wiringPiSetupGpio() == -1) return 1;

    // Set led pin to output mode
    pinMode(LED_R_PIN, OUTPUT);
    pinMode(LED_G_PIN, OUTPUT);
    pinMode(LED_B_PIN, OUTPUT);

    led_status.color = RED;
    led_status.duty = 0;
    led_status.data = OFF;
    return 0;
}

int led_set_color(int new_color)
{
    if (new_color >= LED_COLOR_NUM || new_color < 0) return 1;

    led_status.color = new_color;
    return 0;
}

int led_set_data(int new_data)
{
    if (new_data != ON && new_data != OFF) {
	return 1;
    }

    led_status.data = new_data;
    return 0;
}

int led_set_duty(int new_duty)
{
    led_status.duty = new_duty;
    return 0;
}

int led_status_update(void)
{
    digitalWrite(LED_R_PIN, 0);
    digitalWrite(LED_G_PIN, 0);
    digitalWrite(LED_B_PIN, 0);

    if (led_status.data) {
	switch(led_status.color) {
	case RED:
	     digitalWrite(LED_R_PIN, 1);
	     break;
	case BLUE:
	     digitalWrite(LED_B_PIN, 1);
	     break;
	case GREEN:
	     digitalWrite(LED_G_PIN, 1);
	     break;
	default:
	     digitalWrite(LED_R_PIN, 0);
	     digitalWrite(LED_G_PIN, 0);
	     digitalWrite(LED_B_PIN, 0);
	     break;
	}
    }
    /* printf("color:%d, data %d\n",led_status.color,led_status.data); */
    return 0;
}
