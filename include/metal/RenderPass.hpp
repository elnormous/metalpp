#ifndef METALPP_METAL_RENDERPASS_HPP
#define METALPP_METAL_RENDERPASS_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class RenderPassDescriptor: public ns::Object
    {
    public:
        RenderPassDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::array, ns::sel::alloc), ns::sel::init)}
        {
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
