#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <os/availability.h>
#include <objc/NSObjCRuntime.h>
#include "../objc/Object.hpp"

namespace mtl
{
    class Device;

    enum class ResourceUsage: NSUInteger
    {
        Read   = 1 << 0,
        Write  = 1 << 1,
        Sample API_DEPRECATED_WITH_REPLACEMENT("Read", macos(10.13, 13.0), ios(11.0, 16.0)) = 1 << 2
    } API_AVAILABLE(macos(10.13), ios(11.0));

    enum class BarrierScope: NSUInteger
    {
        Buffers = 1 << 0,
        Textures = 1 << 1,
        RenderTargets API_AVAILABLE(macos(10.14), macCatalyst(13.0)) API_UNAVAILABLE(ios) = 1 << 2,
    } API_AVAILABLE(macos(10.14), ios(12.0));

    class CommandEncoder: public ns::Object
    {
        Device device() const noexcept;
    };
}

#endif
