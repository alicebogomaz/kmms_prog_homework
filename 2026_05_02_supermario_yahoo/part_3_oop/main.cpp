#include <ncurses.h>

#include "game/game.hpp"

using namespace orcinix;

int main() {
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    start_color();
    use_default_colors();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    Game game;
    game.run();
    endwin();
    return 0;

}
