#include "brick.hpp"

namespace orcinix {

    Brick::Brick() : GameObject(0, 0, 0, 0, air) {};
    Brick::Brick(float x, float y,
                 float width, float height,
                 ObjectType type)
        : GameObject(x, y, width, height, type) {};

}
