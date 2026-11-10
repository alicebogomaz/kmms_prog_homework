#pragma once

#include <vector>

#include "game_map.hpp"
#include "console_ui_obj.hpp"

namespace biv {
	class Game;

	class ConsoleGameMap : public GameMap {
		private:
			char** map;
			Game* game;
			
			std::vector<ConsoleUIObject*> objs;
			
		public:
			ConsoleGameMap(const int height, const int width, Game* game);
			~ConsoleGameMap();
			
			void add_obj(ConsoleUIObject*);
			void clear() noexcept override;
			void refresh() noexcept override;
			void remove_obj(ConsoleUIObject*);
			void remove_objs() override;
			void show() const noexcept override;
	};
}
