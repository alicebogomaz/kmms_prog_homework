#pragma once

#include "environment/entities/enemies/enemy.hpp"
#include "environment/level/brick.hpp"
#include "environment/level/coin.hpp"

namespace orcinix {

    class Level {
        private:
            Brick* bricks;
            int bricksCount;

            Coin* coins;
            int coinsCount;

            Enemy* enemies;
            int enemiesCount;

        public:
            Level();
            ~Level();

            void load(int levelNumber);

            Brick* getBricks() const;
            int getBricksCount() const;

            Coin* getCoins() const;
            int getCoinsCount() const;
            void addCoin(float x, float y);
            void removeCoin(int index);

            Enemy* getEnemies() const;
            int getEnemiesCount() const;
            void removeEnemy(int index);
    };

}
