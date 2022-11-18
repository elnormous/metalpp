#ifndef METALPP_METAL_COMMANDQUEUE_HPP
#define METALPP_METAL_COMMANDQUEUE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "CommandBuffer.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    class CommandQueue: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLCommandQueue");

    public:
        CommandQueue() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        CommandQueue(const id p) noexcept: Object{p} {}

        Device device() const noexcept;
        
        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String& label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] CommandBuffer commandBuffer() const noexcept
        {
            const id commandBuffer = objc::sendMessage<id>(*this, sel::commandBuffer);
            return CommandBuffer{objc::sendMessage<id>(commandBuffer, ns::sel::retain)};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
