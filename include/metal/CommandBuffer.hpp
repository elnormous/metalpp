#ifndef METALPP_METAL_COMMANDBUFFER_HPP
#define METALPP_METAL_COMMANDBUFFER_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "../objc/Object.hpp"

namespace mtl
{
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
        CommandBuffer(const id p) noexcept: ns::Object{p} {}

    };
}

#endif
