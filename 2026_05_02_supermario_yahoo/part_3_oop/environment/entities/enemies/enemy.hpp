#pragma once

#include "environment/obj_base/movable.hpp"

namespace orcinix {

    class Enemy : public Movable {
        public:
            Enemy();
            Enemy(float x, float y);

            void walk();
    };

}
