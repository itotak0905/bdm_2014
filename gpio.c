/* GPIOでの入出力に関連する関数群 */

/* と思ったけど外部のライブラリ(とりあえずwiringPi)があるのでそっちを使う */
/* と思ったけどbdmに合わせてもう少し使いやすい関数を作る */
#include "mylib.h"

static led_t led_status;

int led_set_color(int new_color)
{
    return 0;
}

int led_set_mode(int new_mode)
{
    return 0;
}

int led_set_duty(int new_duty)
{
    return 0;
}

int led_status_update(void)
{
    return 0;
}
