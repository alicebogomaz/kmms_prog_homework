#include "level.hpp"

namespace orcinix {

    Level::Level() {
        bricks = nullptr;
        coins = nullptr;
        enemies = nullptr;

        bricksCount = 0;
        coinsCount = 0;
        enemiesCount = 0;
    }

    Level::~Level() {
        delete[] bricks;
        delete[] coins;
        delete[] enemies;
    }

    void Level::load(int levelNumber) {
        delete[] bricks;
        delete[] coins;
        delete[] enemies;

        switch (levelNumber) {

            case 1:
                bricksCount = 13;
                coinsCount = 0;
                enemiesCount = 2;

                bricks = new Brick[bricksCount] {

                    Brick(20, 20, 40, 5, brick),
                    Brick(30, 10, 5, 3, luckyblock),
                    Brick(50, 10, 5, 3, luckyblock),
                    Brick(60, 15, 40, 10, brick),
                    Brick(60, 100, 10, 3, empty_luckyblock_platform),
                    Brick(70, 5, 5, 3, luckyblock),
                    Brick(75, 5, 5, 3, empty_luckyblock_platform),
                    Brick(80, 5, 5, 3, luckyblock),
                    Brick(85, 5, 10, 3, empty_luckyblock_platform),
                    Brick(100, 20, 20, 5, brick),
                    Brick(120, 15, 10, 10, brick),
                    Brick(134, 20, 40, 5,brick),
                    Brick(177, 15, 5, 10, finish)

                };

                enemies = new Enemy[enemiesCount] {

                    Enemy(25, 10),
                    Enemy(80, 10)

                };

                break;

            case 2:
                bricksCount = 6;
                coinsCount = 0;
                enemiesCount = 6;

                bricks = new Brick[bricksCount] {

                    Brick(20, 20, 40, 5, brick),
                    Brick(60, 15, 10, 10, brick),
                    Brick(80, 20, 20, 5, brick),
                    Brick(120, 15, 10, 10, brick),
                    Brick(150, 20, 40, 5, brick),
                    Brick(210, 15, 10, 10, finish)

                };

                enemies = new Enemy[enemiesCount] {

                    Enemy(25, 10),
                    Enemy(80, 10),
                    Enemy(65, 10),
                    Enemy(125, 10),
                    Enemy(160, 10),
                    Enemy(175, 10)
                };

                break;

            case 3:
                bricksCount = 4;
                coinsCount = 0;
                enemiesCount = 6;

                bricks = new Brick[bricksCount] {

                    Brick(20, 20, 40, 5, brick),
                    Brick(80, 20, 15, 5, brick),
                    Brick(120, 15, 15, 10, brick),
                    Brick(160, 10, 15, 15, finish)

                };

                enemies = new Enemy[enemiesCount] {

                    Enemy(25, 10),
                    Enemy(50, 10),
                    Enemy(80, 10),
                    Enemy(90, 10),
                    Enemy(120, 10),
                    Enemy(130, 10)
                };

                break;


            default:

                load(1);

                break;

        }
    }

    Brick* Level::getBricks() const {
        return bricks;
    }

    int Level::getBricksCount() const {
        return bricksCount;
    }

    Coin* Level::getCoins() const {
        return coins;
    }

    int Level::getCoinsCount() const {
        return coinsCount;
    }

    void Level::removeCoin(int index) {
        if (coinsCount <= 0) return;

        Coin* newCoins = new Coin[coinsCount - 1];
        int newIndex = 0;

        for (int i = 0; i < coinsCount; i++) {
            if (i == index) continue;
            newCoins[newIndex] = coins[i];
            newIndex++;
        }

        delete[] coins;
        coins = newCoins;
        coinsCount--;
    }

    Enemy* Level::getEnemies() const {
        return enemies;
    }

    int Level::getEnemiesCount() const {
        return enemiesCount;
    }

    void Level::removeEnemy(int index) {
        if (enemiesCount <= 0) return;

        Enemy* newEnemies = new Enemy[enemiesCount - 1];
        int newIndex = 0;

        for (int i = 0; i < enemiesCount; i++) {
            if (i == index) continue;
            newEnemies[newIndex] = enemies[i];
            newIndex++;
        }

        delete[] enemies;
        enemies = newEnemies;
        enemiesCount--;
    }

}
