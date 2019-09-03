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
#define NUMSKEYS 4
int SKeys[NUMSKEYS] = { 0 };
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
    short i = 0;

    for (;;) {
        if ((ch = getch()) == ERR) {
            /* pass */
        } else {
            switch (ch) {
            case KEY_DOWN:
            case KEY_UP:
            case KEY_LEFT:
            case KEY_RIGHT:
                break;
            }

            /* set key to whether it was pressed or not */
            for (i = 0; i < NUMKEYS; i++)
                Keys[i] = (ch == i);
            
            for (i = 0; i < NUMSKEYS; i++)
                SKeys[i] = (ch - KEY_DOWN) == i;
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
