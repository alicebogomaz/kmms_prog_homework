#include <ncurses.h>
#include <unistd.h>

#include "render.hpp"

namespace orcinix {

    void Render::drawObject(const GameObject& object) {
        for (int y = 0; y < object.getHeight(); y++) {
            for (int x = 0; x < object.getWidth(); x++) {
                mvaddch(object.getY() + y,
                        object.getX() + x,
                        object.getSymbol());
            }
        }
    }

    void Render::drawLevel(const Level& level) {

        for (int i = 0; i < level.getBricksCount(); i++) {
            drawObject(level.getBricks()[i]);
        }

        for (int i = 0; i < level.getEnemiesCount(); i++) {
            drawObject(level.getEnemies()[i]);
        }

        for (int i = 0; i < level.getCoinsCount(); i++) {
            drawObject(level.getCoins()[i]);
        }
    }

    void Render::drawPlayer(const Player& player) {
        drawObject(player);
    }

    void Render::drawUI(const Player& player) {
        mvprintw(1, 5, "Score: %d", player.getScore());
    }

    void Render::deathScreen() {
        bkgd(COLOR_PAIR(2));
        refresh();
        usleep(300000);
        bkgd(COLOR_PAIR(1));
        clear();
        refresh();
    }

    void Render::winScreen() {
        bkgd(COLOR_PAIR(3));
        refresh();
        usleep(300000);
        bkgd(COLOR_PAIR(1));
        clear();
        refresh();
    }

}
