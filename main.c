#include "nce.h"

void nce_resize(int sig)
{
    getmaxyx(stdscr, SHeight, SWidth);
}

void nce_startup()
{
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void nce_update()
{
    for (int i = 0; i < SHeight; i++) {
        for (int j = 0; j < SWidth; j++) {
            swrite("X", j, i);
        }
        swrite("SUPER", 0, i);
    }

    if (Keys['a']) {
        printf("%d, %d\n", SHeight, SWidth);
        Keys['a'] = false;
    }
}

int main()
{
    nce_init();
    return 0;
}
