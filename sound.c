/* 音声出力に関係する関数群 */
#include "mylib.h"
#include "library.h"

static char command[256];

int sound_init(void)
{
    //?
    return 0;
}

int sound_set_title(const char* title)
{
    snprintf(command, sizeof(command), "aplay %s&", title); 
    //さすがにアカンか?
    return 0;
}

int sound_start(void)
{
    system(command);
    return 0;
}

int sound_stop(void)
{
    return 0;
}
