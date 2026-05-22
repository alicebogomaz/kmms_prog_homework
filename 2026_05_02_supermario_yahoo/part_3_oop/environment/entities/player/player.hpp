#pragma once

#include "environment/obj_base/movable.hpp"

namespace orcinix {

    class Player : public Movable {
        private:
            int score;
        public:
            Player(float x, float y);

            void addScore(int amount);
            int getScore() const;

            void moveLeft();
            void moveRight();
    };

}
