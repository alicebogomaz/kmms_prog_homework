#include "console_moving_platform.hpp"

using biv::ConsoleMovingPlatformHoriz;

ConsoleMovingPlatformHoriz::ConsoleMovingPlatformHoriz(const Coord& top_left, int width, int height,
                                                      float hspeed, float left_bound, float right_bound) : MovingPlatformHoriz(top_left, width, height,
                                                                                                                               hspeed, left_bound, right_bound) {}
char ConsoleMovingPlatformHoriz::get_brush() const noexcept {
    return '#';
}
