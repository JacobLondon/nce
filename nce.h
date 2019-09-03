#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * User defined
 */

/* NCE Resize handler */
void ncersize(int sig);
/* NCE Action function */
void nceaction();

/**
 * Internals
 */

void nceinit();
void ncego();

#define NUMKEYS 0xFF
short Keys[NUMKEYS] = { 0 };
int SWidth, SHeight;



void nceinit()
{
    initscr();
    clear();
    cbreak();
    noecho();
    getmaxyx(stdscr, SHeight, SWidth);
    signal(SIGWINCH, &ncersize);
    nodelay(stdscr, true);
    start_color();

    ncego();
}

void ncego()
{
    int ch = 0;
    for (;;) {
        if ((ch = getch()) == ERR) {
            /* pass */
        } else {
            /* set key to whether it was pressed or not */
            for (short i = 0; i < NUMKEYS; i++)
                Keys[i] = (ch == i);
        }

        if (Keys[27]) /* ESCAPE */
            goto Exit;

        nceaction();
    }

Exit:
    endwin();
}

void _chrwrite(char ch, int x, int y)
{
    mvaddch(y, x, ch);
}

void _strwrite(char *s, int x, int y)
{
    move(y, x);
    addstr(s);
}

/* Usage: writeattr(chr, 'a', 5, 10, A_BOLD); */
#define swrite(type, v, x, y, attr) do { \
    attron((attr)); \
    _ ## type ## write((v), (x), (y)); \
    attroff((attr)); \
} while (0)
