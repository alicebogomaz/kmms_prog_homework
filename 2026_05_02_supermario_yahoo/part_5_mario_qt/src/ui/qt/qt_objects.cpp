#include "qt_objects.hpp"

using namespace biv;

QtMario::QtMario(const Coord& top_left, int width, int height) : Rect(top_left, width, height), Mario(top_left, width, height) {}
QString QtMario::get_sprite() const {
    float v = get_speed().v;
    if (v < -0.01)
        return "sprites/mario_jump.png";
    if (v > 0.01)
        return "sprites/mario_fall.png";

    return "sprites/mario_idle.png";
}
bool QtMario::is_facing_right() const noexcept {
    return facing_right;
}
void QtMario::set_facing_right(bool right) noexcept {
    facing_right = right;
}

QtEnemy::QtEnemy(const Coord& top_left, int width, int height) : Rect(top_left, width, height), Enemy(top_left, width, height) {}
QString QtEnemy::get_sprite() const {
    return "sprites/enemy.png";
}

QtFlyingEnemy::QtFlyingEnemy(const Coord& top_left, int width, int height) : Rect(top_left, width, height), FlyingEnemy(top_left, width, height) {}
QString QtFlyingEnemy::get_sprite() const {
    return "sprites/flying_enemy.png";
}

QtJumpingEnemy::QtJumpingEnemy(const Coord& top_left, int width, int height) : Rect(top_left, width, height), JumpingEnemy(top_left, width, height) {}
QString QtJumpingEnemy::get_sprite() const {
    return "sprites/jumping_enemy.png";
}

QtBox::QtBox(const Coord& top_left, int width, int height) : Rect(top_left, width, height), Box(top_left, width, height) {}
QString QtBox::get_sprite() const {
    return "sprites/brick.png";
}

QtFullBox::QtFullBox(const Coord& top_left, int width, int height, UIFactory* factory) : Rect(top_left, width, height), FullBox(top_left, width, height, factory) {}
QString QtFullBox::get_sprite() const {
    if (is_active_) {
        return "sprites/question.png";
    }

    return "sprites/empty_box.png";
}

QtMoney::QtMoney(const Coord& top_left, int width, int height) : Rect(top_left, width, height), Money(top_left, width, height) {}
QString QtMoney::get_sprite() const {
    return "sprites/coin.png";
}

QtShip::QtShip(const Coord& top_left, int width, int height) : Rect(top_left, width, height), Ship(top_left, width, height) {}
QString QtShip::get_sprite() const {
    return "sprites/ship.png";
}

QtMovingPlatformHoriz::QtMovingPlatformHoriz(const Coord& top_left, int width, int height, float hspeed,
                                            float left_bound, float right_bound) : Rect(top_left, width, height), MovingPlatformHoriz(top_left, width, height,
                                                                                                       hspeed, left_bound, right_bound) {}
QString QtMovingPlatformHoriz::get_sprite() const {
    return "sprites/platform.png";
}
