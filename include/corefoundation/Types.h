#ifndef METALPP_COREFOUNDATION_TYPES_HPP
#define METALPP_COREFOUNDATION_TYPES_HPP

#include <CoreFoundation/CFCGTypes.h>

namespace cg
{
    struct Point final
    {
        Point() noexcept = default;
        Point(CGFloat px, CGFloat py) noexcept: x{px}, y{py} {}

        bool operator==(const Point& other) const noexcept
        {
            return other.x == x && other.y == y;
        }

        bool operator!=(const Point& other) const noexcept
        {
            return other.x != x || other.y != y;
        }

        CGFloat x = 0;
        CGFloat y = 0;
    };

    struct Size final
    {
        Size() noexcept = default;
        Size(CGFloat w, CGFloat h) noexcept: width{w}, height{h} {}

        bool operator==(const Size& other) const noexcept
        {
            return other.width == width && other.height == height;
        }

        bool operator!=(const Size& other) const noexcept
        {
            return other.width != width || other.height != height;
        }

        CGFloat width = 0;
        CGFloat height = 0;
    };

    struct Vector final
    {
        Vector() noexcept = default;
        Vector(CGFloat x, CGFloat y) noexcept: dx{x}, dy{y} {}

        bool operator==(const Vector& other) const noexcept
        {
            return other.dx == dx && other.dy == dy;
        }

        bool operator!=(const Vector& other) const noexcept
        {
            return other.dx != dx || other.dy != dy;
        }

        CGFloat dx = 0;
        CGFloat dy = 0;
    };

    struct Rect final
    {
        Rect() noexcept = default;
        Rect(CGFloat x, CGFloat y, CGFloat w, CGFloat h) noexcept: origin{x, y}, size{w, h} {}
        Rect(Point o, Size s) noexcept: origin{o}, size{s} {}

        bool operator==(const Rect& other) const noexcept
        {
            return other.origin == origin && other.size == size;
        }

        bool operator!=(const Rect& other) const noexcept
        {
            return other.origin != origin || other.size != size;
        }

        Point origin;
        Size size;
    };
}

#endif
