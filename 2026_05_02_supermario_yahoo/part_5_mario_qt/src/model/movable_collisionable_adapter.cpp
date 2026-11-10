#include <cmath>

#include "movable_collisionable_adapter.hpp"

using namespace biv;

MovableCollisionableAdapter::MovableCollisionableAdapter(Movable& movable, Collisionable& collisionable) : movable(&movable), collisionable(&collisionable){}

bool MovableCollisionableAdapter::stands_on(const Rect& platform) const noexcept {
    const Rect entity = collisionable->get_rect();

    return collisionable->is_active() && entity.get_right() > platform.get_left() && entity.get_left() < platform.get_right()
    && std::abs(entity.get_bottom() - platform.get_top()) <= 1 && movable->get_vspeed() >= 0;
}

void MovableCollisionableAdapter::carry(float dx) noexcept {
    movable->move_horizontal_offset(dx);
}

Collisionable* MovableCollisionableAdapter::get_collisionable() const noexcept {
    return collisionable;
}
