#ifndef METALPP_COREGRAPHICS_GEOMETRY_HPP
#define METALPP_COREGRAPHICS_GEOMETRY_HPP

#include "Base.hpp"

namespace cg
{
    struct Point final
    {
        Point() noexcept = default;
        Point(const Float px, const Float py) noexcept: x{px}, y{py} {}

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
        Size(const Float w, const Float h) noexcept: width{w}, height{h} {}

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
        Vector(const Float x, const Float y) noexcept: dx{x}, dy{y} {}

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
        Rect(const Float x, const Float y, const Float w, const Float h) noexcept: origin{x, y}, size{w, h} {}
        Rect(const Point o, const Size s) noexcept: origin{o}, size{s} {}

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
