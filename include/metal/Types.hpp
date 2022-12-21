#ifndef METALPP_METAL_TYPES_HPP
#define METALPP_METAL_TYPES_HPP

#include "../objc/Runtime.hpp"

namespace mtl
{
    struct Origin final
    {
        Origin() noexcept = default;
        Origin(const ns::UInteger px, const ns::UInteger py) noexcept: x{px}, y{py} {}
        Origin(const ns::UInteger px, const ns::UInteger py, const ns::UInteger pz) noexcept: x{px}, y{py}, z{pz} {}

        [[nodiscard]] bool operator==(const Origin& other) const noexcept
        {
            return other.x == x && other.y == y && other.z == z;
        }

        [[nodiscard]] bool operator!=(const Origin& other) const noexcept
        {
            return other.x != x || other.y != y || other.z != z;
        }

        ns::UInteger x = 0;
        ns::UInteger y = 0;
        ns::UInteger z = 0;
    };

    struct Size final
    {
        Size() noexcept = default;
        Size(const ns::UInteger w, const ns::UInteger h) noexcept: width{w}, height{h} {}
        Size(const ns::UInteger w, const ns::UInteger h, const ns::UInteger d) noexcept: width{w}, height{h}, depth{d} {}

        [[nodiscard]] bool operator==(const Size& other) const noexcept
        {
            return other.width == width && other.height == height && other.depth == depth;
        }

        [[nodiscard]] bool operator!=(const Size& other) const noexcept
        {
            return other.width != width || other.height != height || other.depth != depth;
        }

        ns::UInteger width = 0;
        ns::UInteger height = 0;
        ns::UInteger depth = 0;
    };

    struct Region final
    {
        Region() noexcept = default;
        Region(const ns::UInteger x, const ns::UInteger y, const ns::UInteger z, const ns::UInteger w, const ns::UInteger h, const ns::UInteger d) noexcept: origin{x, y ,z}, size{w, h, d} {}
        Region(const Origin o, const Size s) noexcept: origin{o}, size{s} {}

        [[nodiscard]] bool operator==(const Region& other) const noexcept
        {
            return other.origin == origin && other.size == size;
        }

        [[nodiscard]] bool operator!=(const Region& other) const noexcept
        {
            return other.origin != origin || other.size != size;
        }

        Origin origin;
        Size size;
    };
}

#endif
