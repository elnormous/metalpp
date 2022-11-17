#ifndef METALPP_METAL_BUFFER_HPP
#define METALPP_METAL_BUFFER_HPP

#include <os/availability.h>
#include "Resource.hpp"

namespace mtl
{
    class Buffer: public Resource
    {
    public:
        Buffer() = delete;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
