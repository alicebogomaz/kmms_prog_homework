#pragma once

#include "environment/entities/player/player.hpp"

namespace orcinix {

    class Keyboard {
        public:
            static void getInput(Player& mario,
                                bool& running);
    };

}
