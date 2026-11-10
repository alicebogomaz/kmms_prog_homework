#include "moving_platforms.hpp"

using biv::MovingPlatformHoriz;

MovingPlatformHoriz::MovingPlatformHoriz(const Coord& top_left, int width, int height,
                               float hspeed, float left_bound, float right_bound) : RectMapMovableAdapter(top_left, width, height),
                                                                                   Movable(top_left, width, height, 0, hspeed){
    this->left_bound = left_bound;
    this->right_bound = right_bound;
    this->movement_x = top_left.x;
    this->moving_right = true;
    this->hspeed = MapMovable::MAP_STEP;
}

void MovingPlatformHoriz::move_horizontally() noexcept {
    const float prev_movement_x = movement_x;

    if (moving_right) {
        movement_x += this->hspeed;
        if (movement_x + width >= right_bound) {
            movement_x = right_bound - width;
            moving_right = false;
        }
    } else {
        movement_x -= this->hspeed;
        if (movement_x <= left_bound) {
            movement_x = left_bound;
            moving_right = true;
        }
    }
    top_left.x += movement_x - prev_movement_x;
}

void MovingPlatformHoriz::move_vertically() noexcept {}

biv::Rect MovingPlatformHoriz::get_rect() const noexcept {
    return {top_left, width, height};
}

biv::Speed MovingPlatformHoriz::get_speed() const noexcept {
    return {vspeed, hspeed};
}

void MovingPlatformHoriz::process_horizontal_static_collision(Rect* obj) noexcept {}

void MovingPlatformHoriz::process_vertical_static_collision(Rect* obj) noexcept {}

void MovingPlatformHoriz::process_mario_collision(Collisionable* mario) noexcept {}

