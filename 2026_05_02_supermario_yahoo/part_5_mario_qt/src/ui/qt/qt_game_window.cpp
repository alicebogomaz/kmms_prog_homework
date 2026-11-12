#include "qt_game_window.hpp"

#include <QVBoxLayout>

#include "first_level.hpp"
#include "qt_objects.hpp"

using namespace biv;

QtGameWindow::QtGameWindow(QWidget* parent) : QWidget(parent), factory(&game), game_map(factory.get_game_map(30, 200)),
                                              game_level(new FirstLevel(&factory)), mario(factory.get_mario()) {

    setWindowTitle("Super Mario");
    setFocusPolicy(Qt::StrongFocus);
    game_map->setFocusPolicy(Qt::NoFocus);

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(game_map);

    connect(&timer, &QTimer::timeout, this, &QtGameWindow::update_game);

    timer.start(50);
}

void QtGameWindow::keyPressEvent(QKeyEvent* event) {
    if (event->isAutoRepeat())
        return;

    int key = event->key();
    pressed_keys.insert(key);

    if (key == Qt::Key_Space || key == Qt::Key_Up || key == Qt::Key_W) {
        jump_requested = true;
    }

    if (key == Qt::Key_Escape) {
        game.finish();
        timer.stop();
        close();
    }
}

void QtGameWindow::keyReleaseEvent(QKeyEvent* event) {
    if (!event->isAutoRepeat()) {
        pressed_keys.remove(event->key());
    }
}

void QtGameWindow::handle_input() {
    mario->set_moving(false);
    if (pressed_keys.contains(Qt::Key_Left) || pressed_keys.contains(Qt::Key_A)) {
        mario->move_map_right();

        if (!game.check_static_collisions(mario)) {
            game.move_map_right();
            mario->set_moving(true);
        }

        mario->move_map_left();
        mario->set_facing_right(false);
    }
    else if (pressed_keys.contains(Qt::Key_Right) || pressed_keys.contains(Qt::Key_D)) {
        mario->move_map_left();

        if (!game.check_static_collisions(mario)) {
            game.move_map_left();
            mario->set_moving(true);
        }

        mario->move_map_right();
        mario->set_facing_right(true);
    }

    if (jump_requested) {
        mario->jump();
        jump_requested = false;
    }
}

void QtGameWindow::update_game() {
    if (game.is_finished()) {
        timer.stop();
        close();
        return;
    }

    handle_input();

    game.move_objs_horizontally();
    game.move_objs_on_platform();
    game.check_horizontally_static_collisions();

    game.move_objs_vertically();
    game.check_mario_collision();
    game.check_vertically_static_collisions();

    if (game_map->is_below_map(mario->get_top()) || !mario->is_active()) {
        game.reset_score();
        game_level->restart();
        mario = factory.get_mario();

        pressed_keys.clear();
        jump_requested = false;

        game_map->refresh();
        pause_game();
        return;
    }

    if (game.is_level_end()) {
        if (!game_level->is_final()) {
            game_level = game_level->get_next();
            mario = factory.get_mario();

            game.start_level();

            pressed_keys.clear();
            jump_requested = false;

            game_map->refresh();
            pause_game();
            return;
        }

        game.finish();
        timer.stop();
        close();
        return;
    }

    game_map->refresh();
}

void QtGameWindow::pause_game() {
    timer.stop();

    QTimer::singleShot(1000, this, [this]() {
        if (!game.is_finished()) {
            timer.start(50);
        }
    });
}
