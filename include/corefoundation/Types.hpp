#ifndef METALPP_COREFOUNDATION_TYPES_HPP
#define METALPP_COREFOUNDATION_TYPES_HPP

#include <CoreFoundation/CFCGTypes.h>

namespace cg
{
    using Float = CGFloat;

    struct Point final
    {
        Point() noexcept = default;
        Point(Float px, Float py) noexcept: x{px}, y{py} {}

        [[nodiscard]] bool operator==(const Point& other) const noexcept
        {
            return other.x == x && other.y == y;
        }

        [[nodiscard]] bool operator!=(const Point& other) const noexcept
        {
            return other.x != x || other.y != y;
        }

        Float x = 0;
        Float y = 0;
    };

    struct Size final
    {
        Size() noexcept = default;
        Size(Float w, Float h) noexcept: width{w}, height{h} {}

        [[nodiscard]] bool operator==(const Size& other) const noexcept
        {
            return other.width == width && other.height == height;
        }

        [[nodiscard]] bool operator!=(const Size& other) const noexcept
        {
            return other.width != width || other.height != height;
        }

        Float width = 0;
        Float height = 0;
    };

    struct Vector final
    {
        Vector() noexcept = default;
        Vector(Float x, Float y) noexcept: dx{x}, dy{y} {}

        [[nodiscard]] bool operator==(const Vector& other) const noexcept
        {
            return other.dx == dx && other.dy == dy;
        }

        [[nodiscard]] bool operator!=(const Vector& other) const noexcept
        {
            return other.dx != dx || other.dy != dy;
        }

        Float dx = 0;
        Float dy = 0;
    };

    struct Rect final
    {
        Rect() noexcept = default;
        Rect(Float x, Float y, Float w, Float h) noexcept: origin{x, y}, size{w, h} {}
        Rect(Point o, Size s) noexcept: origin{o}, size{s} {}

        [[nodiscard]] bool operator==(const Rect& other) const noexcept
        {
            return other.origin == origin && other.size == size;
        }

        [[nodiscard]] bool operator!=(const Rect& other) const noexcept
        {
            return other.origin != origin || other.size != size;
        }

        Point origin;
        Size size;
    };
}

#endif
