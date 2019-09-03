#include "nce.h"

void ncersize(int sig)
{
    getmaxyx(stdscr, SHeight, SWidth);
}

void nceaction()
{
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    for (int i = 0; i < SHeight; i++) {
        for (int j = 0; j < SWidth; j++) {
            swrite(chr, 'X', j, i, A_NORMAL);
        }
        swrite(str, "SUPER", 0, i, A_NORMAL);
    }
}

int main()
{
    nceinit();
    return 0;
}
