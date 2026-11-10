#pragma once

#include "rect_map_movable_adapter.hpp"
#include "collisionable.hpp"
#include "movable.hpp"

namespace biv {
    class MovingPlatformHoriz : public RectMapMovableAdapter, public Collisionable, public Movable {
    private:
        float left_bound;
        float right_bound;
        float movement_x;
        bool moving_right;

    public:
        MovingPlatformHoriz(const Coord& top_left, int width, int height,
                       float hspeed, float left_bound, float right_bound);

        void move_horizontally() noexcept override;
        void move_vertically() noexcept override;

        Rect get_rect() const noexcept override;
        Speed get_speed() const noexcept override;

        void process_horizontal_static_collision(Rect*) noexcept override;
        void process_vertical_static_collision(Rect*) noexcept override;
        void process_mario_collision(Collisionable*) noexcept override;
    };
}
