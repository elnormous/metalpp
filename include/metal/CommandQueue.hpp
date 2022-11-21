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
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        CommandQueue(const id p) noexcept: Object{p} {}

        [[nodiscard]] Device device() const noexcept;
        
        [[nodiscard]] ns::String label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] CommandBuffer commandBuffer() const noexcept
        {
            return getRetained<CommandBuffer>(sel::commandBuffer);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
