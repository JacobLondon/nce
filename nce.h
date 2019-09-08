#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * User defined
 */

/* user overide */
void nce_onrsize(int sig);
void nce_onstartup();
void nce_onupdate();

/**
 * Prototypes
 */

void nce_start();
void nce_go();

/**
 * Globals
 */

/* ascii chars */
#define NUMKEYS 0xFF
/* which Keys are pressed */
bool Keys[NUMKEYS] = { 0 };
const int KEY_ESCAPE = 27;

/* special chars */
#define NUMSKEYS 6
/* use SKeyIDs to index into SKeyLookup */
enum SKeyIDs {
    SKEY_DOWN,
    SKEY_UP,
    SKEY_LEFT,
    SKEY_RIGHT,
    SKEY_BACKSPACE,
    SKEY_ENTER,
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

void nce_start()
{
    initscr();
    clear();
    cbreak();
    noecho();
    getmaxyx(stdscr, SHeight, SWidth);
    signal(SIGWINCH, &nce_onrsize);
    nodelay(stdscr, true);
    start_color();

    nce_onstartup();
    nce_go();
}

void nce_go()
{
    int ch = 0;
    short i = 0;

    for (;;) {
        if ((ch = getch()) == ERR) {
            /* pass */
        }
        else {
            /* set key to whether it was pressed or not */
            for (i = 0; i < NUMKEYS; i++)
                Keys[i] = (ch == i);
            
            for (i = 0; i < NUMSKEYS; i++)
                SKeys[i] = (ch == SKeyLookup[i]);
        }

        /* ESCAPE */
        if (Keys[KEY_ESCAPE])
            goto Exit;

        nce_onupdate();
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
