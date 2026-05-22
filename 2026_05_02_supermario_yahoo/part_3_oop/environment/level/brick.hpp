#pragma once

#include "environment/obj_base/gameObject.hpp"

namespace orcinix {

    class Brick : public GameObject {
        public:
            Brick();
            Brick(float x, float y,
                  float width, float height,
                  ObjectType type);
    };

}
