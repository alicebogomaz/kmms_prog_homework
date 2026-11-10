#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* ThirdLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({30, 10}, 3, 3);

	ui_factory->create_full_box({65, 2}, 5, 3);
	ui_factory->create_box({60, 2}, 5, 3);
	ui_factory->create_full_box({55, 2}, 5, 3);
	ui_factory->create_box({150, 15}, 10, 3);
	ui_factory->create_full_box({160, 15}, 5, 3);
	ui_factory->create_full_box({175, 15}, 5, 3);
	ui_factory->create_box({180, 15}, 10, 3);

	ui_factory->create_moving_platform({20, 25}, 15, 2, 0.5, 20, 60);
	ui_factory->create_moving_platform({65, 20}, 10, 2, 0.5, 83, 110);
	ui_factory->create_moving_platform({45, 10}, 7, 2, 0.5, 47, 80);
	ui_factory->create_moving_platform({140, 25}, 10, 2, 0.5, 140, 200);
	ui_factory->create_moving_platform({132, 10}, 10, 2, 0.5, 132, 200);
	ui_factory->create_moving_platform({232, 25}, 5, 2, 0.5, 232, 250);
	ui_factory->create_moving_platform({255, 25}, 5, 2, 0.5, 255, 500);

	ui_factory->create_ship({45, -10}, 2, 25);
	ui_factory->create_ship({60, 25}, 10, 2);
	ui_factory->create_ship({83, 10}, 2, 2);
	ui_factory->create_ship({80, 20}, 3, 2);
	ui_factory->create_ship({108, 13}, 2, 2);
	ui_factory->create_ship({110, 3}, 2, 32);
	ui_factory->create_ship({130, -10}, 2, 30);
	ui_factory->create_ship({130, 25}, 10, 2);
	ui_factory->create_ship({168, 20}, 5, 2);
	ui_factory->create_ship({132, 20}, 2, 2);
	ui_factory->create_ship({195, 5}, 10, 2);

	ui_factory->create_ship({200, 5}, 2, 30);

	ui_factory->create_ship({225, -10}, 2, 30);

	ui_factory->create_ship({225, 25}, 7, 2);
	ui_factory->create_ship({250, 25}, 5, 2);


	ui_factory->create_ship({395, 5}, 2, 5);
	ui_factory->create_ship({395, 12}, 2, 2);
	ui_factory->create_ship({397, 14}, 12, 2);
	ui_factory->create_ship({409, 12}, 2, 2);
	ui_factory->create_ship({409, 5}, 2, 5);

	ui_factory->create_ship({500, 25}, 5, 5);

	ui_factory->create_enemy({152, 10}, 3, 2);
	ui_factory->create_enemy({177, 10}, 3, 2);
	ui_factory->create_jumping_enemy({80, 15}, 3, 2);
	ui_factory->create_jumping_enemy({137, 20}, 3, 2);
	ui_factory->create_jumping_enemy({251, 20}, 3, 2);
	ui_factory->create_jumping_enemy({162, 20}, 3, 2);
	ui_factory->create_flying_enemy({60, 5}, 3, 2);
	ui_factory->create_flying_enemy({112, 13}, 3, 2);
	ui_factory->create_flying_enemy({132, 5}, 3, 2);
	ui_factory->create_flying_enemy({220, 10}, 3, 2);
	ui_factory->create_flying_enemy({227, 15}, 3, 2);
	ui_factory->create_flying_enemy({345, 15}, 3, 2);
	ui_factory->create_flying_enemy({420, 15}, 3, 2);
}
