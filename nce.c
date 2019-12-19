#include "nce.h"


/**
 * Globals
 */

/* which Keys are pressed */
bool Keys[NUMKEYS] = { 0 };
const int KEY_ESCAPE = 27;

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
int SWidth;
int SHeight;

/**
 * Definitions
 */

void nce_init()
{
    initscr();
    clear();
    cbreak();
    noecho();
    getmaxyx(stdscr, SHeight, SWidth);
    signal(SIGWINCH, &nce_resize);
    nodelay(stdscr, true);
    start_color();

    nce_startup();
    nce_run();
}

void nce_run()
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

        nce_update();
    }

Exit:
    endwin();
}

void nce_goto(int x, int y)
{
    move(y, x);
}

void nce_write(char *s, int x, int y)
{
    move(y, x);
    addstr(s);
}

bool nce_keypressed(bool key[], unsigned index)
{
    if (key[index]) {
        key[index] = false;
        return true;
    }
    return false;
}
