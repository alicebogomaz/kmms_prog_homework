#include "physics.hpp"

namespace orcinix {

    bool Physics::isCollision(const GameObject& a,
                              const GameObject& b)
    {
        return !(
            a.getX() + a.getWidth() < b.getX() ||
            a.getX() > b.getX() + b.getWidth() ||
            a.getY() + a.getHeight() < b.getY() ||
            a.getY() > b.getY() + b.getHeight()
        );
    }

    bool Physics::hasGroundAhead(const Movable& object, const Level& level) {
        float checkX;

        if (object.getHorizSpeed() > 0) {
            checkX = object.getX() + object.getWidth() + 1;

        } else {
            checkX = object.getX() - 1;

        }

        float checkY = object.getY() + object.getHeight() + 1;

        for (int i = 0; i < level.getBricksCount(); i++) {
            Brick& brick = level.getBricks()[i];

            if (checkX >= brick.getX() &&
                checkX <= brick.getX() + brick.getWidth() &&
                checkY >= brick.getY() &&
                checkY <= brick.getY() + brick.getHeight()) {

                return true;
            }
        }

        return false;

    }

    void Physics::horizMoveObject(Movable& object, Level& level) {

        if (object.getType() == enemy_walking &&
            !Physics::hasGroundAhead(object, level)) {
            object.setHorizSpeed(-object.getHorizSpeed());

        }

        object.setPos(object.getX() + object.getHorizSpeed(), object.getY());

        for (int i = 0; i < level.getBricksCount(); i++) {
            Brick& brick = level.getBricks()[i];

            if (isCollision(object, brick) &&
                object.getY() + object.getHeight() > brick.getY() + 1 &&
                object.getY() < brick.getY() + brick.getHeight() - 1) {

                object.setPos(object.getX() - object.getHorizSpeed(), object.getY());

                if (object.getType() == enemy_walking || object.getType() == coin) {
                    object.setHorizSpeed(-object.getHorizSpeed());
                }

                return;
            }
        }
    }

    void Physics::vertMoveObject(Movable& object, Level& level) {
        object.setIsFly(true);
        object.setVertSpeed(object.getVertSpeed() + 0.05);
        object.setPos(object.getX(),
                      object.getY() + object.getVertSpeed());

        for (int i = 0; i < level.getBricksCount(); i++) {

            Brick& brick = level.getBricks()[i];

            if (!isCollision(object, brick)) continue;

            if (object.getVertSpeed() > 0 &&
                object.getY() + object.getHeight() - object.getVertSpeed() <= brick.getY()) {

                object.setPos(object.getX(), brick.getY() - object.getHeight());

                object.setVertSpeed(0);
                object.setIsFly(false);

            } else {

                object.setPos(object.getX(), object.getY() + brick.getHeight());
                object.setVertSpeed(0);

                if (brick.getType() == luckyblock) {
                    brick.setType(empty_luckyblock_platform);

                    level.addCoin(brick.getX() + brick.getWidth() / 2, brick.getY() - 6);
                }

            }
        }

        return;
    }

}
