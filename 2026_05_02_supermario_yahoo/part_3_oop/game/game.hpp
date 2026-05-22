#pragma once

#include "level.hpp"
#include "environment/entities/player/player.hpp"

namespace orcinix {

    class Game {
        private:
            Player mario;
            Level level;

            bool running;
            bool isDead;
            bool levelCompleted;

            int currentLevel;

            void input();
            void update();
            void render();
            void resetLevel();
            void nextLevel();

        public:
            Game();
            void run();
    };

}
