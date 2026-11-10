#pragma once

#include "qt_ui_obj.hpp"
#include "rect.hpp"

namespace biv {
    class QtUIObjectRectAdapter : virtual public Rect, public QtUIObject {
        public:
            QtUIObjectRectAdapter();
            QtUIObjectRectAdapter(const Coord& top_left, int width, int height);

            int get_height() const noexcept override;
            int get_width() const noexcept override;
            float get_x() const noexcept override;
            float get_y() const noexcept override;
    };
}
