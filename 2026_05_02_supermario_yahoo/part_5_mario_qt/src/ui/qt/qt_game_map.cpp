#include "qt_game_map.hpp"
#include "game.hpp"

#include <algorithm>
#include <QPaintEvent>
#include <QCoreApplication>
#include <QDir>

using biv::QtGameMap;

QtGameMap::QtGameMap(int height, int width, Game* game) : QWidget(nullptr), GameMap(height, width), game(game) {
    setMinimumSize(640, 480);
    setWindowTitle("Mario");
}

const QPixmap& QtGameMap::load_sprite(const QString& path) {
    if (!sprites.contains(path)) {
        QString full_path = QDir(QCoreApplication::applicationDirPath()).filePath(path);

        QPixmap pixmap(full_path);

        sprites.insert(path, QPixmap(full_path));
    }

    return sprites[path];
}

void QtGameMap::add_obj(QtUIObject* obj) {
    objs.push_back(obj);
}

void QtGameMap::clear() noexcept {
    update();
}

void QtGameMap::refresh() noexcept {
    update();
}

void QtGameMap::remove_obj(QtUIObject* obj) {
    objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
}

void QtGameMap::remove_objs() {
    objs.clear();
}

void QtGameMap::show() const noexcept {
    const_cast<QtGameMap*>(this)->QWidget::show();
}

void QtGameMap::draw_object(QPainter& painter, QtUIObject* obj) {
    const QPixmap& sprite = load_sprite(obj->get_sprite());

    if (sprite.isNull())
        return;

    QRectF target(obj->get_x() * CELL_SIZE, obj->get_y() * CELL_SIZE,
                 obj->get_width() * CELL_SIZE, obj->get_height() * CELL_SIZE);

    painter.save();

    if (!obj->is_facing_right()) {
        painter.translate(2 * target.x() + target.width(), 0);
        painter.scale(-1, 1);
    }

    painter.drawPixmap(target, sprite, QRectF(sprite.rect()));
    painter.restore();
}


void QtGameMap::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    QPainter painter(this);

    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    const QPixmap& sky = load_sprite("sprites/sky.png");
    painter.drawPixmap(rect(), sky);
    painter.save();
    painter.translate(QWidget::width() / 2.0 - 40.5*CELL_SIZE, 0);

    for (QtUIObject* obj : objs) {
        draw_object(painter, obj);
    }

    painter.restore();

    painter.setPen(Qt::black);
    painter.drawText(10, 20, QString("SCORE: %1").arg(game->get_score()));
}
