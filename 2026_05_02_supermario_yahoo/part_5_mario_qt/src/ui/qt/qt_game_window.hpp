#pragma once

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QSet>

#include "game.hpp"
#include "game_level.hpp"
#include "qt_ui_factory.hpp"

namespace biv {

    class QtGameWindow : public QWidget {
    private:
        Game game;
        QtUIFactory factory;

        QtGameMap* game_map;
        GameLevel* game_level;
        QtMario* mario;

        QTimer timer;
        QSet<int> pressed_keys;
        bool jump_requested = false;

        void handle_input();
        void update_game();
        void pause_game();

    protected:
        void keyPressEvent(QKeyEvent* event) override;
        void keyReleaseEvent(QKeyEvent* event) override;

    public:
        QtGameWindow(QWidget* parent = nullptr);
    };

}
