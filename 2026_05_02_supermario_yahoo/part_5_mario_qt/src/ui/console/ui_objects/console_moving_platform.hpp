#pragma once

#include "moving_platforms.hpp"
#include "console_ui_obj_rect_adapter.hpp"

namespace biv {
    class ConsoleMovingPlatformHoriz : public MovingPlatformHoriz, public ConsoleUIObjectRectAdapter {
        public:
            ConsoleMovingPlatformHoriz(const Coord& top_left, int width, int height, float hspeed, float left_bound, float right_bound);
            char get_brush() const noexcept override;

    };
}
