#ifndef METALPP_METAL_TEXTURE_HPP
#define METALPP_METAL_TEXTURE_HPP

#include "Resource.hpp"

namespace mtl
{
    class Texture: public Resource
    {
    public:
        Texture(const id p) noexcept: Resource{p} {}

    };
}

#endif
