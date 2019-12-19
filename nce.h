#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <ncurses.h>

/**
 * User defined
 */

/* user overide */
void nce_resize(int sig);
void nce_startup();
void nce_update();

/**
 * Prototypes
 */

void nce_init();
void nce_run();
void nce_goto(int x, int y);
void nce_write(char *s, int x, int y);
bool nce_keypressed(bool key[], unsigned index);

/**
 * Globals
 */

/* ascii chars */
#define NUMKEYS 0xFF
/* which Keys are pressed */
extern bool Keys[NUMKEYS];
extern const int KEY_ESCAPE;

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
extern int SKeyLookup[NUMSKEYS];
/* which SKeys are pressed */
extern bool SKeys[NUMSKEYS];

/* screen width and height */
extern int SWidth;
extern int SHeight;
