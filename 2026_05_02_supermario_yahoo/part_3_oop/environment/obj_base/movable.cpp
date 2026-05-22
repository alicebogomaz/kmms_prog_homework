#include "movable.hpp"

namespace orcinix {

    Movable::Movable(float x, float y,
                     float width, float height,
                     ObjectType type)
            : GameObject(x, y, width, height, type)
    {
        horizSpeed = 0.2;
        vertSpeed = 0;

        isFly = false;
    }

    void Movable::move() {
        x += horizSpeed;
    }

    float Movable::getHorizSpeed() const {
        return horizSpeed;
    }

    float Movable::getVertSpeed() const {
        return vertSpeed;
    }

    bool Movable::getIsFly() const {
        return isFly;
    }

    void Movable::setHorizSpeed(float speed) {
        horizSpeed = speed;
    }

    void Movable::setVertSpeed(float speed) {
        vertSpeed = speed;
    }

    void Movable::setIsFly(bool state) {
        isFly = state;
    }
}
