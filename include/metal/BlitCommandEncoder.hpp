#ifndef METALPP_METAL_BLITCOMMANDENCODER_HPP
#define METALPP_METAL_BLITCOMMANDENCODER_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "CommandEncoder.hpp"

namespace mtl
{
    enum class BlitOption: NSUInteger
    {
        None                       = 0,
        DepthFromDepthStencil      = 1 << 0,
        StencilFromDepthStencil    = 1 << 1,
        RowLinearPVRTC API_AVAILABLE(ios(9.0), macos(11.0), macCatalyst(14.0)) = 1 << 2,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    class BlitCommandEncoder final: public CommandEncoder
    {
    public:
        BlitCommandEncoder() = delete;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
