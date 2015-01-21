/* GPIOでの入出力に関連する関数群 */

/* と思ったけど外部のライブラリ(とりあえずwiringPi)があるのでそっちを使う */
/* と思ったけどbdmに合わせてもう少し使いやすい関数を作る */
#include "library.h"
#include "mylib.h"

static fcled_t fcled_status;
static led_t rled_status;


int all_led_init(void)
{ 
    // Set fcled pin to output mode

    pinMode(FCLED_R_PIN, OUTPUT);
    pinMode(FCLED_G_PIN, OUTPUT);
    pinMode(FCLED_B_PIN, OUTPUT);
    pinMode(RLED_PIN, OUTPUT);

    fcled_status.color_r = 0;
    fcled_status.color_b = 0;
    fcled_status.color_g = 0;
    fcled_status.duty = 0;
    fcled_status.data = OFF;

    rled_status.duty = 0;
    rled_status.data = OFF;

    return 0;
}

int fcled_set_color_value(int new_color, int new_value)
{
    if (new_color >= FCLED_COLOR_NUM || new_color < 0) return 1;
    if (new_value > 100) new_value = 100;
    else if (new_value < 0) new_value = 0;
    switch (new_color) {
    case RED:
	fcled_status.color_r = new_value;
	break;
    case BLUE:
	fcled_status.color_b = new_value;
	break;
    case GREEN:
	fcled_status.color_g = new_value;
	break;
    default:
	break;
    }
    return 0;
}

int fcled_set_data(int new_data)
{
    if (new_data != ON && new_data != OFF) {
	return 1;
    }

    fcled_status.data = new_data;
    return 0;
}

int rled_set_data(int new_data)
{
    if (new_data != ON && new_data != OFF) {
	return 1;
    }

    rled_status.data = new_data;
    return 0;
}

int fcled_set_duty(int new_duty)
{
    fcled_status.duty = new_duty;
    return 0;
}

int rled_set_duty(int new_duty)
{
    rled_status.duty = new_duty;
    return 0;
}

int fcled_status_update(void)
{
    static int counter = 0;

    digitalWrite(FCLED_R_PIN, 1);
    digitalWrite(FCLED_G_PIN, 0);
    digitalWrite(FCLED_B_PIN, 0);

    if (fcled_status.data) {
	if (fcled_status.color_r > counter) {
	    digitalWrite(FCLED_R_PIN, 0);
	}
	if (fcled_status.color_g > counter) {
	    digitalWrite(FCLED_G_PIN, 1);
	}
	if (fcled_status.color_b > counter) {
	    digitalWrite(FCLED_B_PIN, 1);
	}

    }
    counter++;
    if (counter >= 100) counter = 0; 
    return 0;
}

int rled_status_update(void)
{
    if (rled_status.data == ON) {
	digitalWrite(RLED_PIN, 1);
    } else {
	digitalWrite(RLED_PIN, 0);
    }
    return 0;
}

int all_led_status_update(void)
{
    rled_status_update();
    fcled_status_update();
    return 0;
}
