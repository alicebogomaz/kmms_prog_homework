#pragma once

#include "environment/obj_base/movable.hpp"

namespace orcinix {

    class Coin : public Movable {
        public:
            Coin();
            Coin(float x, float y);
    };

}
