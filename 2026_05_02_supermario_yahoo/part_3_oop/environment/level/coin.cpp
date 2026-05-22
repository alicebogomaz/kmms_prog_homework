#include "coin.hpp"

namespace orcinix {
    Coin::Coin() :  Movable(0, 0, 0, 0, air) {};
    Coin::Coin(float x, float y) : Movable(x, y, 3, 2, coin) {};
}
