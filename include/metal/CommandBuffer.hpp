#ifndef METALPP_METAL_COMMANDBUFFER_HPP
#define METALPP_METAL_COMMANDBUFFER_HPP

#include <os/availability.h>
#include <CoreFoundation/CFDate.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "BlitCommandEncoder.hpp"
#include "ComputeCommandEncoder.hpp"
#include "Drawable.hpp"
#include "ParallelRenderCommandEncoder.hpp"
#include "RenderCommandEncoder.hpp"
#include "RenderPass.hpp"

namespace mtl
{
    class Device;
    class CommandQueue;

    enum class CommandBufferStatus: ns::UInteger
    {
        NotEnqueued = 0,
        Enqueued = 1,
        Committed = 2,
        Scheduled = 3,
        Completed = 4,
        Error = 5,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class CommandBufferError: ns::UInteger
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

    enum class CommandBufferErrorOption: ns::UInteger
    {
        None = 0,
        EncoderExecutionStatus = 1 << 0,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    enum class CommandEncoderErrorState: ns::Integer
    {
        Unknown = 0,
        Completed = 1,
        Affected = 2,
        Pending = 3,
        Faulted = 4,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    class CommandBufferDescriptor final: public ns::Object
    {
    public:
        static constexpr bool copying = true;
    };

    class CommandBuffer: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(commandQueue, "commandQueue");
        METALPP_PRIVATE_SEL(retainedReferences, "retainedReferences");
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(presentDrawable_, "presentDrawable:");
        METALPP_PRIVATE_SEL(presentDrawable_atTime_, "presentDrawable:atTime:");
        METALPP_PRIVATE_SEL(enqueue, "enqueue");
        METALPP_PRIVATE_SEL(commit, "commit");
        METALPP_PRIVATE_SEL(waitUntilCompleted, "waitUntilCompleted");
        METALPP_PRIVATE_SEL(status, "status");
        METALPP_PRIVATE_SEL(blitCommandEncoder, "blitCommandEncoder");
        METALPP_PRIVATE_SEL(renderCommandEncoderWithDescriptor_, "renderCommandEncoderWithDescriptor:");
        METALPP_PRIVATE_SEL(computeCommandEncoder, "computeCommandEncoder");
        METALPP_PRIVATE_SEL(parallelRenderCommandEncoderWithDescriptor_, "parallelRenderCommandEncoderWithDescriptor:");
        METALPP_PRIVATE_SEL(pushDebugGroup_, "pushDebugGroup:");
        METALPP_PRIVATE_SEL(popDebugGroup, "popDebugGroup");

        using Object::Object;
        using Object::operator=;
        
        CommandBuffer() = delete;

        [[nodiscard]] Device device() const noexcept;
        [[nodiscard]] CommandQueue commandQueue() const noexcept;

        [[nodiscard]] auto retainedReferences() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(retainedReferences)) == YES;
        }

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        void presentDrawable(const Drawable& drawable) const noexcept
        {
            sendMessage(METALPP_SEL(presentDrawable_), drawable.get());
        }

        void presentDrawable(const Drawable& drawable, const CFTimeInterval presentationTime) const noexcept
        {
            sendMessage(METALPP_SEL(presentDrawable_atTime_), drawable.get(), presentationTime);
        }

        void enqueue() noexcept
        {
            sendMessage(METALPP_SEL(enqueue));
        }

        void commit() noexcept
        {
            sendMessage(METALPP_SEL(commit));
        }

        void waitUntilCompleted() noexcept
        {
            sendMessage(METALPP_SEL(waitUntilCompleted));
        }

        [[nodiscard]] auto status() const noexcept
        {
            return sendMessage<CommandBufferStatus>(METALPP_SEL(status));
        }

        [[nodiscard]] auto blitCommandEncoder() noexcept
        {
            return BlitCommandEncoder{sendMessage<id>(METALPP_SEL(blitCommandEncoder))};
        }

        [[nodiscard]] auto renderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor) noexcept
        {
            return RenderCommandEncoder{sendMessage<id>(METALPP_SEL(renderCommandEncoderWithDescriptor_), renderPassDescriptor.get())};
        }

        [[nodiscard]] auto computeCommandEncoder() noexcept
        {
            return ComputeCommandEncoder{sendMessage<id>(METALPP_SEL(computeCommandEncoder))};
        }

        [[nodiscard]] auto parallelRenderCommandEncoder(const RenderPassDescriptor& renderPassDescriptor) noexcept
        {
            return ParallelRenderCommandEncoder{sendMessage<id>(METALPP_SEL(parallelRenderCommandEncoderWithDescriptor_), renderPassDescriptor.get())};
        }

        void pushDebugGroup(const ns::String& string) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(pushDebugGroup_), string.get());
        }

        void popDebugGroup() noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(popDebugGroup));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
