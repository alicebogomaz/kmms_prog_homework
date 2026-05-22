#include "gameObject.hpp"

namespace orcinix {

    GameObject::GameObject(float x, float y,
                           float width, float height,
                           ObjectType type)
    {
        this->x = x;
        this->y = y;

        this->width = width;
        this->height = height;

        this->type = type;
    }

    float GameObject::getX() const {
        return x;
    }

    float GameObject::getY() const {
        return y;
    }

    float GameObject::getHeight() const {
        return height;
    }

    float GameObject::getWidth() const {
        return width;
    }

    char GameObject::getSymbol() const {
        return (char)type;
    }

    ObjectType GameObject::getType() const {
        return type;
    }

    void GameObject::setPos(float newX, float newY) {
        x = newX;
        y = newY;
    }

    void GameObject::setType(ObjectType newType) {
        type = newType;
    }

}
