#include "qt_ui_factory.hpp"

using namespace biv;

QtUIFactory::QtUIFactory(Game* game): UIFactory(game) {}

void QtUIFactory::clear_data() {
    game->remove_objs();
    if (game_map != nullptr)
        game_map->remove_objs();

    delete mario;
    mario = nullptr;
    for (QtBox* obj : boxes)
        delete obj;
    for (QtFullBox* obj : full_boxes)
        delete obj;
    for (QtShip* obj : ships)
        delete obj;
    for (QtEnemy* obj : enemies)
        delete obj;
    for (QtFlyingEnemy* obj : flying_enemies)
        delete obj;
    for (QtJumpingEnemy* obj : jumping_enemies)
        delete obj;
    for (QtMoney* obj : moneys)
        delete obj;
    for (QtMovingPlatformHoriz* obj : moving_platforms)
        delete obj;
    boxes.clear();
    full_boxes.clear();
    ships.clear();
    enemies.clear();
    flying_enemies.clear();
    jumping_enemies.clear();
    moneys.clear();
    moving_platforms.clear();
}

void QtUIFactory::create_box(const Coord& top_left, int width, int height) {
    QtBox* box = new QtBox(top_left, width, height);

    boxes.push_back(box);
    game->add_map_movable(box);
    game->add_static_obj(box);
    game_map->add_obj(box);
}

void QtUIFactory::create_enemy(const Coord& top_left, int width, int height) {
    QtEnemy* enemy = new QtEnemy(top_left, width, height);

    enemies.push_back(enemy);
    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
    game->add_platform_passanger(enemy, enemy);
    game_map->add_obj(enemy);
}

void QtUIFactory::create_flying_enemy(const Coord& top_left, int width, int height) {
    QtFlyingEnemy* enemy = new QtFlyingEnemy(top_left, width, height);

    flying_enemies.push_back(enemy);
    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
    game->add_platform_passanger(enemy, enemy);
    game_map->add_obj(enemy);
}

void QtUIFactory::create_full_box(const Coord& top_left, int width, int height) {
    QtFullBox* box = new QtFullBox(top_left, width, height, this);

    full_boxes.push_back(box);
    game->add_collisionable(box);
    game->add_map_movable(box);
    game->add_static_obj(box);
    game_map->add_obj(box);
}

void QtUIFactory::create_jumping_enemy(const Coord& top_left, int width, int height) {
    QtJumpingEnemy* enemy = new QtJumpingEnemy(top_left, width, height);

    jumping_enemies.push_back(enemy);
    game->add_map_movable(enemy);
    game->add_movable(enemy);
    game->add_collisionable(enemy);
    game->add_platform_passanger(enemy, enemy);
    game_map->add_obj(enemy);
}

void QtUIFactory::create_mario(const Coord& top_left, int width, int height) {
    if (mario != nullptr) {
        game->remove_collisionable(mario);
        game->remove_movable(mario);
        game->remove_mario();
        if (game_map != nullptr)
            game_map->remove_obj(mario);

        delete mario;
    }

    mario = new QtMario(top_left, width, height);

    game->add_collisionable(mario);
    game->add_movable(mario);
    game->add_mario(mario);
    if (game_map != nullptr)
        game_map->add_obj(mario);
}

void QtUIFactory::create_money(const Coord& top_left, int width, int height) {
    QtMoney* money = new QtMoney(top_left, width, height);

    moneys.push_back(money);
    game->add_map_movable(money);
    game->add_movable(money);
    game->add_collisionable(money);
    game_map->add_obj(money);
}

void QtUIFactory::create_moving_platform(const Coord& top_left, int width, int height,
                                         float hspeed, float left_bound, float right_bound) {
    QtMovingPlatformHoriz* platform = new QtMovingPlatformHoriz(top_left, width, height,
                                                                MapMovable::MAP_STEP, left_bound, right_bound);

    moving_platforms.push_back(platform);
    game->add_map_movable(platform);
    game->add_movable(platform);
    game->add_static_obj(platform);
    game->add_moving_platform(platform, platform);
    game_map->add_obj(platform);
}

void QtUIFactory::create_ship(const Coord& top_left, int width, int height) {
    QtShip* ship = new QtShip(top_left, width, height);

    ships.push_back(ship);
    game->add_map_movable(ship);
    game->add_static_obj(ship);
    game_map->add_obj(ship);
}

QtGameMap* QtUIFactory::get_game_map(int height, int width) {
    if (game_map == nullptr) {
        game_map = new QtGameMap(height, width, game);
    }

    return game_map;
}

QtMario* QtUIFactory::get_mario() {
    return mario;
}
