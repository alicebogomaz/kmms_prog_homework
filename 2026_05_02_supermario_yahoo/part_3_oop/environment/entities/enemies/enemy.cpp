#include "enemy.hpp"

namespace orcinix {
    Enemy::Enemy() : Movable(0, 0, 0, 0, air) {};
    Enemy::Enemy(float x, float y) : Movable (x, y, 3, 2, enemy_walking) {};

    void Enemy::walk() {
        move();
    }

}
