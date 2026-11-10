#include "qt_ui_obj_rect_adapter.hpp"

using biv::QtUIObjectRectAdapter;

QtUIObjectRectAdapter::QtUIObjectRectAdapter() = default;

QtUIObjectRectAdapter::QtUIObjectRectAdapter(const Coord& top_left, int width, int height) : Rect(top_left, width, height) {}

int QtUIObjectRectAdapter::get_height() const noexcept {
    return Rect::get_height();
}

float QtUIObjectRectAdapter::get_x() const noexcept {
    return Rect::get_x();
}

float QtUIObjectRectAdapter::get_y() const noexcept {
    return Rect::get_y();
}

int QtUIObjectRectAdapter::get_width() const noexcept {
    return width;
}
