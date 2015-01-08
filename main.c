#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    led_init();
    adc_init();
    sound_init();

    printf("test\n");
    
    return 0;
}
