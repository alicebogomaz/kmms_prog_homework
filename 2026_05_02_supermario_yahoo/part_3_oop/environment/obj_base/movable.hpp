#pragma once

#include "gameObject.hpp"

namespace orcinix {

    class Movable : public GameObject {

        protected:
            float vertSpeed, horizSpeed;
            bool isFly;

        public:
            Movable(float x, float y,
                    float width, float height,
                    ObjectType type);
            void move();

            float getHorizSpeed() const;
            float getVertSpeed() const;

            bool getIsFly() const;
            void setIsFly(bool state);

            void setHorizSpeed(float speed);
            void setVertSpeed(float speed);
    };

}
