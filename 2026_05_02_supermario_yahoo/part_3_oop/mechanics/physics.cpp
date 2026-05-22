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

    void Physics::horizMoveObject(Movable& object, Level& level) {
        object.setPos(object.getX() + object.getHorizSpeed(), object.getY());

        for (int i = 0; i < level.getBricksCount(); i++) {
            Brick& brick = level.getBricks()[i];

            if (isCollision(object, brick) &&
                object.getY() + object.getHeight() > brick.getY() + 1 &&
                object.getY() < brick.getY() + brick.getHeight() - 1) {
                    object.setPos(object.getX() - object.getHorizSpeed(), object.getY());

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

            if (object.getVertSpeed() > 0) {
                object.setPos(object.getX(), brick.getY() - object.getHeight());

                object.setVertSpeed(0);
                object.setIsFly(false);

            } else {

                object.setPos(object.getX(), object.getY() + brick.getHeight());
                object.setVertSpeed(0);

                if (brick.getType() == luckyblock) {
                    brick.setType(empty_luckyblock_platform);
                }

            }
        }

        return;
    }

}
