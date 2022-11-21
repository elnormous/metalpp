#ifndef METALPP_METAL_COMMANDBUFFER_HPP
#define METALPP_METAL_COMMANDBUFFER_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include <CoreFoundation/CFDate.h>
#include "../objc/Object.hpp"
#include "BlitCommandEncoder.hpp"
#include "Drawable.hpp"
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

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] BlitCommandEncoder blitCommandEncoder() const noexcept
        {
            return getRetained<BlitCommandEncoder>(sel::blitCommandEncoder);
        }

        [[nodiscard]] RenderCommandEncoder renderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor) const noexcept
        {
            return getRetained<RenderCommandEncoder>(sel::renderCommandEncoderWithDescriptor_, static_cast<id>(renderPassDescriptor));
        }

        void presentDrawable(const Drawable& drawable) const noexcept
        {
            sendMessage(sel::presentDrawable_, static_cast<id>(drawable));
        }

        void presentDrawable(const Drawable& drawable, const CFTimeInterval presentationTime) const noexcept
        {
            sendMessage(sel::presentDrawable_atTime_, static_cast<id>(drawable), presentationTime);
        }

        void commit() noexcept
        {
            sendMessage(sel::commit);
        }

        void waitUntilCompleted() noexcept
        {
            sendMessage(sel::waitUntilCompleted);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
