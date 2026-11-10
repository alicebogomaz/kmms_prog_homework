#include "game.hpp"
#include "movable_collisionable_adapter.hpp"

#include <algorithm>

using biv::Game;

Game::Game() {}

void Game::add_collisionable(Collisionable* obj) {
	collisionable_objs.push_back(obj);
}

void Game::add_map_movable(MapMovable* obj) {
	map_movable_objs.push_back(obj);
}

void Game::add_mario(Mario* obj) {
	mario = obj;
	add_platform_passanger(obj, obj);
}

void Game::add_movable(Movable* obj) {
	movable_objs.push_back(obj);
}

void Game::add_platform_passanger(Movable* movable, Collisionable* collisionable) {
	platform_passangers.push_back(MovableCollisionableAdapter(*movable, *collisionable));
}

void Game::add_moving_platform(Movable* movable, Rect* rect) {
	moving_platforms.push_back({movable, rect});
}

void Game::add_static_obj(Rect* obj) {
	static_objs.push_back(obj);
}

void Game::check_horizontally_static_collisions() noexcept {
	for (Collisionable* obj: collisionable_objs) {
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_horizontal_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::check_mario_collision() {
	for (int i = 0; i < collisionable_objs.size(); i++) {
		Collisionable* obj = collisionable_objs[i];
		if (obj->has_collision(mario)) {
			obj->process_mario_collision(mario);
			if (!mario->is_active()) {
				break;
			} else if (!obj->is_active()) {
				score += obj->get_score();
				collisionable_objs[i] = collisionable_objs.back();
				collisionable_objs.pop_back();
				i--;
			}
		}
	}
}

bool Game::check_static_collisions(Collisionable* obj) const noexcept {
	for (Rect* static_obj: static_objs) {
		if (obj->has_collision(static_obj)) {
			return true;
		}
	}
	return false;
}

void Game::check_vertically_static_collisions() noexcept {
	if (mario->has_collision(static_objs[static_objs.size() - 1])) {
		is_level_end_ = true;
	}
	
	for (Collisionable* obj: collisionable_objs) {
		for (Rect* static_obj: static_objs) {
			if (obj->has_collision(static_obj)) {
				obj->process_vertical_static_collision(static_obj);
				break;
			}
		}
	}
}

void Game::finish() noexcept {
	is_finished_ = true;
}

bool Game::is_finished() const noexcept {
	return is_finished_;
}

bool Game::is_level_end() const noexcept {
	return is_level_end_;
}

void Game::move_map_left() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_left();
	}
}

void Game::move_map_right() noexcept {
	for (MapMovable* obj: map_movable_objs) {
		obj->move_map_right();
	}
}

bool Game::is_mario_on_platform(const Rect& platform) const noexcept {
	for (const auto& passanger : platform_passangers) {
		if (passanger.get_collisionable() == mario) {
			return passanger.stands_on(platform);
		}
	}
	return false;
}

void Game::move_objs_on_platform() noexcept {
	for (const auto& platform : moving_platforms) {
		Movable* movable = platform.first;
		Rect* rect = platform.second;
		const Rect old_rect = *rect;
		const float old_x = rect->get_x();

		bool mario_on_platform = is_mario_on_platform(old_rect);

		std::vector<MovableCollisionableAdapter> passangers;

		for (const auto& passanger : platform_passangers) {
			if (passanger.stands_on(old_rect)) {
				passangers.push_back(passanger);
			}
		}

		movable->move_horizontally();

		const float dx = rect->get_x() - old_x;

		for (auto& passanger : passangers) {
			passanger.carry(dx);
		}

		if (mario_on_platform) {
			if (dx > 0) {
				move_map_left();
			}
			else if (dx < 0) {
				move_map_right();
			}

			mario->move_horizontal_offset(-dx);
		}
	}
}

void Game::move_objs_horizontally() noexcept {
	for (Movable* obj : movable_objs) {
		bool is_platform = false;
		for (const auto& platform : moving_platforms) {
			if (platform.first == obj) {
				is_platform = true;
				break;
			}
		}

		if (!is_platform) {
			obj->move_horizontally();
		}
	}
}

void Game::move_objs_vertically() noexcept {
	for (Movable* obj: movable_objs) {
		obj->move_vertically();
	}
}

void Game::remove_collisionable(Collisionable* obj) {
	for (size_t i = 0; i  < platform_passangers.size(); ++i) {
		if (platform_passangers[i].get_collisionable() == obj) {
			platform_passangers.erase(platform_passangers.begin() + i);
			break;
		}
	}
	remove_obj(collisionable_objs, obj);
}

void Game::remove_map_movable(MapMovable* obj) {
	remove_obj(map_movable_objs, obj);
}

void Game::remove_mario() noexcept {
	mario = nullptr;
}

void Game::remove_movable(Movable* obj) {
	remove_obj(movable_objs, obj);
}

void Game::remove_objs() {
	platform_passangers.clear();
	moving_platforms.clear();
	collisionable_objs.clear();
	map_movable_objs.clear();
	movable_objs.clear();
	static_objs.clear();
	remove_mario();
}

void Game::remove_static_obj(Rect* obj) {
	remove_obj(static_objs, obj);
}

void Game::start_level() noexcept {
	is_level_end_ = false;
}

void Game::add_score(const int points) noexcept {
	score += points;
}

void Game::reset_score() noexcept {
	score = 0;
}

int Game::get_score() const noexcept {
	return score;
}

// ----------------------------------------------------------------------------
// 									PRIVATE
// ----------------------------------------------------------------------------
template<class T>
void Game::remove_obj(std::vector<T*>& container, T* obj) {
	container.erase(
		std::remove(
			container.begin(), container.end(), obj
		), 
		container.end()
	);
}
