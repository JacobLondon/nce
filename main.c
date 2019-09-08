#include "nce.h"

void nce_onrsize(int sig)
{
    getmaxyx(stdscr, SHeight, SWidth);
}

void nce_onstartup()
{
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
}

void nce_onupdate()
{
    for (int i = 0; i < SHeight; i++) {
        for (int j = 0; j < SWidth; j++) {
            swrite(chr, 'X', j, i, A_NORMAL);
        }
        swrite(str, "SUPER", 0, i, A_NORMAL);
    }

    if (Keys['a']) {
        printf("%d, %d\n", SHeight, SWidth);
        Keys['a'] = false;
    }
}

int main()
{
    nce_start();
    return 0;
}
