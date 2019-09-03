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
 * Prototypes
 */

void nceinit();
void ncego();

/**
 * Globals
 */

/* ascii chars */
#define NUMKEYS 0xFF
/* which Keys are pressed */
bool Keys[NUMKEYS] = { 0 };

/* special chars */
#define NUMSKEYS 6
/* use SKeyIDs to index into SKeyLookup */
enum SKeyIDs {
    KDOWN,
    KUP,
    KLEFT,
    KRIGHT,
    KBACKSPACE,
    KENTER,
};
/* the characters getch() returns */
int SKeyLookup[NUMSKEYS] = {
    KEY_DOWN,
    KEY_UP,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_BACKSPACE,
    KEY_ENTER,
};
/* which SKeys are pressed */
bool SKeys[NUMSKEYS] = { false };

/* screen width and height */
int SWidth, SHeight;

/**
 * Definitions
 */

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
            /* set key to whether it was pressed or not */
            for (i = 0; i < NUMKEYS; i++)
                Keys[i] = (ch == i);
            
            for (i = 0; i < NUMSKEYS; i++) {
                /* this is broken */
                SKeys[i] = (ch == i);
            }
        }

        /* ESCAPE */
        if (Keys[27])
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
