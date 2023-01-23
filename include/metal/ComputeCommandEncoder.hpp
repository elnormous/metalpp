#ifndef METALPP_METAL_COMPUTECOMMANDENCODER_HPP
#define METALPP_METAL_COMPUTECOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "CommandEncoder.hpp"
#include "Fence.hpp"

namespace mtl
{
    class ComputeCommandEncoder final: public CommandEncoder
    {
    public:
        METALPP_PRIVATE_SEL(updateFence_, "updateFence:");
        METALPP_PRIVATE_SEL(waitForFence_, "waitForFence:");
        
        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        ComputeCommandEncoder() = delete;

        void updateFence(const Fence& fence) noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            sendMessage(METALPP_SEL(updateFence_), fence.get());
        }

        void waitForFence(const Fence& fence) noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            sendMessage(METALPP_SEL(waitForFence_), fence.get());
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
