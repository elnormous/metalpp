#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <objc/NSObjCRuntime.h>
#include "../objc/Object.hpp"

namespace mtl
{
    enum class ResourceUsage: NSUInteger
    {
        Read   = 1 << 0,
        Write  = 1 << 1,
        Sample = 1 << 2
    };

    enum class BarrierScope: NSUInteger
    {
        Buffers = 1 << 0,
        Textures = 1 << 1,
        RenderTargets = 1 << 2,
    };

    class CommandEncoder: public ns::Object
    {

    };
}

#endif
