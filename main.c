#include "mylib.h"
#include "library.h"

int main(void)
{
    /* init周りゴニョゴニョ */
    printf("test\n");
    sound_set_title("Rear_Center.wav");
    sound_start();
    printf("test2\n");
    fflush(stdout);
    usleep(100000);
    sound_start();
    return 0;
}
