#include "player.hpp"

namespace orcinix {

    Player::Player(float x, float y) : Movable(x, y, 3, 3, mario) {
        score = 0;
    }

    void Player::addScore(int amount) {
        score += amount;
    }

    int Player::getScore() const {
        return score;
    }

    void Player::jump() {
        if (!isFly) {
            vertSpeed = -0.9;
            isFly = true;
        }
    }

    void Player::moveLeft() {
        x -= horizSpeed;
    }

    void Player::moveRight() {
        x += horizSpeed;
    }
}
