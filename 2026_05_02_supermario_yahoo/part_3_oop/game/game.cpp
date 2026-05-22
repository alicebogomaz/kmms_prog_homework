#include <ncurses.h>

#include "game.hpp"
#include "mechanics/render.hpp"
#include "mechanics/physics.hpp"
#include "mechanics/keyboard.hpp"

namespace orcinix {

    Game::Game() : mario(20, 12) {
        running = true;
        isDead = false;

        levelCompleted = false;
        currentLevel = 1;

        level.load(currentLevel);
    }

    void Game::input() {
        Keyboard::getInput(mario, running);
    }

    void Game::update() {
        Physics::horizMoveObject(mario, level);
        Physics::vertMoveObject(mario, level);

        for (int i = 0; i < level.getEnemiesCount(); i++) {
            Enemy& enemy = level.getEnemies()[i];

            Physics::horizMoveObject(enemy, level);
            Physics::vertMoveObject(enemy, level);

            if (Physics::isCollision(mario, enemy)) {
                if (mario.getVertSpeed() > 0) {

                    mario.setVertSpeed(-0.7);

                    mario.addScore(50);
                    level.removeEnemy(i);
                    i--;

                } else {
                    isDead = true;
                }
            }

        }

        for (int i = 0; i < level.getCoinsCount(); i++) {

            Coin& coin = level.getCoins()[i];

            if (Physics::isCollision(mario, coin)) {
                mario.addScore(100);
                level.removeCoin(i);
                i--;
            }
        }

        if (mario.getY() > 40) {
            isDead = true;
        }

        for (int i = 0; i < level.getBricksCount(); i++) {
            Brick& brick = level.getBricks()[i];

            if (brick.getType() != finish) continue;
            if (Physics::isCollision(mario, brick)) {
                levelCompleted = true;
            }
        }

        if (isDead) {
            Render::deathScreen();
            resetLevel();
        }

        if (levelCompleted) {
            Render::winScreen();
            nextLevel();
        }
    }

    void Game::resetLevel() {
        mario.setPos(20, 12);
        mario.setVertSpeed(0);
        mario.setHorizSpeed(0);
        level.load(currentLevel);
        isDead = false;
    }

    void Game::render() {
        clear();
        Render::drawLevel(level);
        Render::drawPlayer(mario);
        Render::drawUI(mario);
        refresh();
    }

    void Game::nextLevel() {
        currentLevel++;

        if (currentLevel > 3) {
            currentLevel = 1;
        }

        level.load(currentLevel);

        mario.setPos(20, 12);
        mario.setVertSpeed(0);
        mario.setHorizSpeed(0);

        levelCompleted = false;
    }

    void Game::run() {
        while (running) {
            input();
            update();
            render();
            napms(30);
        }
    }

}
