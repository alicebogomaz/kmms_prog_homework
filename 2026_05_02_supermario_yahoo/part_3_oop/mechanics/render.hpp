#pragma once

#include "game/level.hpp"
#include "environment/entities/player/player.hpp"

namespace orcinix {

    class Render {
        public:
            static void drawLevel(const Level& level);
            static void drawObject(const GameObject& object);
            static void drawPlayer(const Player& player);
            static void drawUI(const Player& player);
            static void deathScreen();
            static void winScreen();
    };

}
