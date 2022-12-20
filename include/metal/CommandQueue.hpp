#ifndef METALPP_METAL_COMMANDQUEUE_HPP
#define METALPP_METAL_COMMANDQUEUE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "CommandBuffer.hpp"

namespace mtl
{
    class Device;

    class CommandQueue: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(commandBuffer, "commandBuffer");

        using Object::Object;

        CommandQueue() = delete;

        [[nodiscard]] Device device() const noexcept;
        
        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        [[nodiscard]] auto commandBuffer() const noexcept
        {
            return CommandBuffer{sendMessage<id>(METALPP_SEL(commandBuffer))};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
