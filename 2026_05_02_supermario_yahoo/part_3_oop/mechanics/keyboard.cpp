#include <ncurses.h>

#include "keyboard.hpp"

namespace orcinix {

    void Keyboard::getInput(Player& mario, bool& running){
        int ch = getch();

        if (ch == 'a') {
            mario.setHorizSpeed(-0.5);

        } else if (ch == 'd') {
            mario.setHorizSpeed(0.5);

        } else if (ch == ' ') {
            if (!mario.getIsFly()) mario.jump();

        } else if (ch == 27) {
            running = false;

        } else {
            mario.setHorizSpeed(0);
        }
    }

}
