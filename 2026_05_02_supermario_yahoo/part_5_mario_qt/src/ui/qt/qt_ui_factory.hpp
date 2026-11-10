#pragma once

#include <vector>

#include "ui_factory.hpp"
#include "qt_game_map.hpp"
#include "qt_objects.hpp"

namespace biv {

    class QtUIFactory : public UIFactory {
        private:
            QtGameMap* game_map = nullptr;

            QtMario* mario = nullptr;

            std::vector<QtBox*> boxes;
            std::vector<QtFullBox*> full_boxes;
            std::vector<QtShip*> ships;

            std::vector<QtEnemy*> enemies;
            std::vector<QtFlyingEnemy*> flying_enemies;
            std::vector<QtJumpingEnemy*> jumping_enemies;

            std::vector<QtMoney*> moneys;
            std::vector<QtMovingPlatformHoriz*> moving_platforms;

        public:
            QtUIFactory(Game* game);

            void clear_data() override;

            void create_box(const Coord& top_left, int width, int height) override;
            void create_enemy(const Coord& top_left, int width, int height) override;
            void create_flying_enemy(const Coord& top_left, int width, int height) override;
            void create_full_box(const Coord& top_left, int width, int height) override;
            void create_jumping_enemy(const Coord& top_left, int width, int height) override;
            void create_mario(const Coord& top_left, int width, int height) override;
            void create_money(const Coord& top_left, int width, int height) override;
            void create_moving_platform(const Coord& top_left, int width, int height,
                                        float hspeed, float left_bound, float right_bound) override;
            void create_ship(const Coord& top_left, int width, int height) override;

            QtGameMap* get_game_map(int height, int width) override;
            QtMario* get_mario() override;
    };

}
