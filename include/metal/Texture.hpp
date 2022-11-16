#ifndef METALPP_METAL_TEXTURE_HPP
#define METALPP_METAL_TEXTURE_HPP

#include <os/availability.h>
#include "Resource.hpp"

namespace mtl
{
    class Texture: public Resource
    {
    public:
        Texture(const id p) noexcept: Resource{p} {}

    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
