#pragma once

#include "objectTypes.hpp"

namespace orcinix {

    class GameObject {

        protected:
            float x, y;
            float width, height;
            ObjectType type;

        public:
            GameObject(float x, float y,
                       float width, float height,
                       ObjectType type);
            virtual ~GameObject() = default;

            float getX() const;
            float getY() const;

            float getHeight() const;
            float getWidth() const;

            char getSymbol() const;
            ObjectType getType() const;

            void setPos(float newX, float newY);
    };

}
