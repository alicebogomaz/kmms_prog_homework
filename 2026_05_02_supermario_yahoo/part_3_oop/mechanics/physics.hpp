#pragma once

#include "environment/obj_base/movable.hpp"
#include "game/level.hpp"

namespace orcinix {

    class Physics {
        public:
            static bool isCollision(const GameObject& a,
                                    const GameObject& b);

            static bool hasGroundAhead(const Movable& object,
                                const Level& level);
            static void horizMoveObject(Movable& object,
                                        Level& level);
            static void vertMoveObject(Movable& object,
                                       Level& level);
    };

}
