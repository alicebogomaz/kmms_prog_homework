#pragma once

#include <QString>

namespace biv {
    class QtUIObject {
    public:
        virtual ~QtUIObject() = default;

        virtual int get_left() const noexcept = 0;
        virtual int get_top() const noexcept = 0;
        virtual int get_width() const noexcept = 0;
        virtual int get_height() const noexcept = 0;

        virtual QString get_sprite() const = 0;
        virtual bool is_facing_right() const noexcept;

        virtual float get_x() const noexcept = 0;
        virtual float get_y() const noexcept = 0;
    };
}
