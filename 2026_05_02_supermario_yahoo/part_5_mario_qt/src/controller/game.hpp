/**
	- Как объекты раскладываются по контейнерам?
*/

#pragma once

#include <vector>
#include <utility>

#include "collisionable.hpp"
#include "map_movable.hpp"
#include "mario.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "movable_collisionable_adapter.hpp"

namespace biv {
	class Game {
		private:
			std::vector<MapMovable*> map_movable_objs;
			std::vector<Rect*> static_objs;
			std::vector<Collisionable*> collisionable_objs;
			std::vector<Movable*> movable_objs;
			std::vector<MovableCollisionableAdapter> platform_passangers;
			std::vector<std::pair<Movable*, Rect*>> moving_platforms;
			
			Mario* mario = nullptr;
			
			bool is_finished_ = false;
			bool is_level_end_ = false;
			int score = 0;

		public:
			Game();
			
			void add_collisionable(Collisionable*);
			void add_map_movable(MapMovable*);
			void add_mario(Mario*);
			void add_movable(Movable*);
			void add_static_obj(Rect*);
			void add_moving_platform(Movable*, Rect*);
			void add_platform_passanger(Movable*, Collisionable*);

			
			void check_horizontally_static_collisions() noexcept;
			void check_mario_collision();
			bool check_static_collisions(Collisionable* obj) const noexcept;
			void check_vertically_static_collisions() noexcept;
			
			void finish() noexcept;
			
			bool is_finished() const noexcept;
			bool is_level_end() const noexcept;
			bool is_mario_on_platform(const Rect& platform) const noexcept;

			void add_score(const int points) noexcept;
			int get_score() const noexcept;
			void reset_score() noexcept;

			
			void move_map_left() noexcept;
			void move_map_right() noexcept;
			void move_objs_horizontally() noexcept;
			void move_objs_vertically() noexcept;
			void move_objs_on_platform() noexcept;
			
			void remove_collisionable(Collisionable*);
			void remove_map_movable(MapMovable*);
			void remove_mario() noexcept;
			void remove_movable(Movable*);
			void remove_objs();
			void remove_static_obj(Rect*);
			void remove_moving_platform(Movable*);
			
			void start_level() noexcept;

		private:
			template<class T>
			void remove_obj(std::vector<T*>& container, T* obj);
	};
}
