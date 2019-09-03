#include <ncurses.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void ncersize(int sig);

void nceinit()
{
    initscr();
    clear();
    cbreak();
    noecho();
    signal(SIGWINCH, &ncersize);
    nodelay(stdscr, TRUE);
}