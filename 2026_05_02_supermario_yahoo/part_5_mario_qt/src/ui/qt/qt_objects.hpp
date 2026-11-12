#pragma once

#include "qt_ui_obj_rect_adapter.hpp"

#include "box.hpp"
#include "enemy.hpp"
#include "full_box.hpp"
#include "mario.hpp"
#include "money.hpp"
#include "moving_platforms.hpp"
#include "ship.hpp"

namespace biv {

    class QtMario : public Mario, public QtUIObjectRectAdapter {
        private:
            bool facing_right = true;
            bool moving = false;
        public:
            QtMario(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
            bool is_facing_right() const noexcept override;
            void set_facing_right(bool right) noexcept;
            void set_moving(bool value) noexcept;
    };

    class QtEnemy : public Enemy, public QtUIObjectRectAdapter {
        public:
            QtEnemy(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
    };

    class QtFlyingEnemy : public FlyingEnemy, public QtUIObjectRectAdapter {
        public:
            QtFlyingEnemy(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
    };

    class QtJumpingEnemy : public JumpingEnemy, public QtUIObjectRectAdapter {
        public:
            QtJumpingEnemy(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
    };

    class QtBox : public Box, public QtUIObjectRectAdapter {
        public:
            QtBox(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
    };

    class QtFullBox : public FullBox, public QtUIObjectRectAdapter {
        public:
            QtFullBox(const Coord& top_left, int width, int height, UIFactory* factory);
            QString get_sprite() const override;
    };

    class QtMoney : public Money, public QtUIObjectRectAdapter {
        public:
            QtMoney(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
    };

    class QtShip : public Ship, public QtUIObjectRectAdapter {
        public:
            QtShip(const Coord& top_left, int width, int height);
            QString get_sprite() const override;
    };

    class QtMovingPlatformHoriz : public MovingPlatformHoriz, public QtUIObjectRectAdapter {
        public:
            QtMovingPlatformHoriz(const Coord& top_left, int width, int height,
                                  float hspeed, float left_bound, float right_bound);
            QString get_sprite() const override;
    };

}
