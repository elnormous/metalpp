#ifndef METALPP_METAL_BUFFER_HPP
#define METALPP_METAL_BUFFER_HPP

#include "Resource.hpp"

namespace mtl
{
    class Buffer: public Resource
    {
    public:
        Buffer(const id p) noexcept: Resource{p} {}

    };
}

#endif
