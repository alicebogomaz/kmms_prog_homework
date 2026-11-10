#include "console_enemy.hpp"

using biv::ConsoleFlyingEnemy;
using biv::ConsoleJumpingEnemy;
using biv::ConsoleEnemy;

ConsoleEnemy::ConsoleEnemy(const Coord& top_left, const int width, const int height) 
	: Enemy(top_left, width, height) {}

char ConsoleEnemy::get_brush() const noexcept {
	return 'e';
}

ConsoleFlyingEnemy::ConsoleFlyingEnemy(const biv::Coord& top_left, const int width, const int height)
: FlyingEnemy(top_left, width, height) {}

char ConsoleFlyingEnemy::get_brush() const noexcept {
	return '&';
}

ConsoleJumpingEnemy::ConsoleJumpingEnemy(const biv::Coord& top_left, const int width, const int height)
: JumpingEnemy(top_left, width, height) {}

char ConsoleJumpingEnemy::get_brush() const noexcept {
	return '^';
}
