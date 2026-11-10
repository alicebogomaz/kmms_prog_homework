#pragma once

#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QHash>

#include <vector>

#include "game_map.hpp"
#include "qt_ui_obj.hpp"

namespace biv {
    class Game;

    class QtGameMap : public QWidget, public GameMap {
        private:
            static constexpr int CELL_SIZE = 24;

            Game* game;
            std::vector<QtUIObject*> objs;
            QHash<QString, QPixmap> sprites;

            const QPixmap& load_sprite(const QString& path);
            void draw_object(QPainter& painter, QtUIObject* obj);

        protected:
            void paintEvent(QPaintEvent* event) override;

        public:
            QtGameMap(int height, int width, Game* game);

            void add_obj(QtUIObject* obj);
            void clear() noexcept override;
            void refresh() noexcept override;
            void remove_obj(QtUIObject* obj);
            void remove_objs() override;
            void show() const noexcept override;
    };
}
