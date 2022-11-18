#ifndef METALPP_METAL_COMMANDBUFFER_HPP
#define METALPP_METAL_COMMANDBUFFER_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "BlitCommandEncoder.hpp"
#include "RenderCommandEncoder.hpp"
#include "RenderPass.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    enum class CommandBufferStatus: NSUInteger
    {
        NotEnqueued = 0,
        Enqueued = 1,
        Committed = 2,
        Scheduled = 3,
        Completed = 4,
        Error = 5,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class CommandBufferError: NSUInteger
    {
        None = 0,
        Internal = 1,
        Timeout = 2,
        PageFault = 3,
        Blacklisted API_DEPRECATED_WITH_REPLACEMENT("AccessRevoked", macos(10.11, 13.0), ios(8.0, 16.0)) = 4,
        AccessRevoked = 4,
        NotPermitted = 7,
        OutOfMemory = 8,
        InvalidResource = 9,
        Memoryless API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(10.0)) = 10,
        DeviceRemoved API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios) = 11,
        StackOverflow API_AVAILABLE(macos(12.0), ios(15.0)) = 12,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class CommandBufferErrorOption: NSUInteger
    {
        None = 0,
        EncoderExecutionStatus = 1 << 0,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    enum class CommandEncoderErrorState: NSInteger
    {
        Unknown = 0,
        Completed = 1,
        Affected = 2,
        Pending = 3,
        Faulted = 4,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    class CommandBuffer: public ns::Object
    {
    public:
        CommandBuffer() = delete;

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

        [[nodiscard]] BlitCommandEncoder blitCommandEncoder() const noexcept
        {
            const id blitCommandEncoder = objc::sendMessage<id>(*this, sel::blitCommandEncoder);
            return BlitCommandEncoder{objc::sendMessage<id>(blitCommandEncoder, ns::sel::retain)};
        }

        [[nodiscard]] RenderCommandEncoder renderCommandEncoderWithDescriptor(const RenderPassDescriptor& renderPassDescriptor) const noexcept
        {
            const id renderCommandEncoder = objc::sendMessage<id>(*this, sel::renderCommandEncoderWithDescriptor_, static_cast<id>(renderPassDescriptor));
            return RenderCommandEncoder{objc::sendMessage<id>(renderCommandEncoder, ns::sel::retain)};
        }

    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
