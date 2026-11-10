#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({30, 10}, 3, 3);
	
	ui_factory->create_full_box({40, 10}, 5, 3);
	ui_factory->create_full_box({65, 2}, 5, 3);
	ui_factory->create_full_box({80, 10}, 5, 3);
	ui_factory->create_box({85, 10}, 10, 3);
	ui_factory->create_full_box({95, 10}, 5, 3);
	ui_factory->create_box({150, 13}, 5, 3);
	ui_factory->create_full_box({155, 13}, 5, 3);

	ui_factory->create_moving_platform({45, 10}, 10, 2, 0.5, 45, 80);

	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_ship({60, 20}, 10, 7);
	ui_factory->create_ship({80, 20}, 20, 7);
	ui_factory->create_ship({110, 20}, 10, 2);
	ui_factory->create_ship({110, 13}, 10, 2);
	ui_factory->create_ship({130, 25}, 40, 2);
	ui_factory->create_ship({200, 20}, 10, 7);

	ui_factory->create_enemy({25, 5}, 3, 2);
	ui_factory->create_enemy({60, 15}, 3, 2);
	ui_factory->create_enemy({145, 35}, 3, 2);
	ui_factory->create_jumping_enemy({167, 20}, 3, 2);
	ui_factory->create_flying_enemy({120, 13}, 3, 2);
}
