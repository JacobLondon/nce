#include "nce.h"

int main()
{
    nceinit();
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_RED);
    init_pair(2, COLOR_RED, COLOR_BLUE);

    int ch;
    for (;;) {
        if ((ch = getch()) == ERR) {
            /* user hasn't responded */
        }
        else {
            switch (ch) {
            case 'Q':
                goto Exit;
            }
        }
    }

Exit:
    endwin();
    return 0;
}

void ncersize(int sig)
{
    int nh, nw;
    getmaxyx(stdscr, nh, nw);
}