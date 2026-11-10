#pragma once

#include <cmath>

#include "movable.hpp"
#include "collisionable.hpp"

namespace biv {

    class MovableCollisionableAdapter {
        private:
            Movable* movable;
            Collisionable* collisionable;

        public:
            MovableCollisionableAdapter(Movable& movable, Collisionable& collisionable);

            bool stands_on(const Rect& platform) const noexcept;

            void carry(float dx) noexcept;

            Collisionable* get_collisionable() const noexcept;

    };

}
