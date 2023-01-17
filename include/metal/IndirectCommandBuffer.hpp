#ifndef METALPP_METAL_INDIRECTCOMMANDBUFFER_HPP
#define METALPP_METAL_INDIRECTCOMMANDBUFFER_HPP

#include <os/availability.h>
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Object.hpp"
#include "../foundation/Range.hpp"
#include "CommandEncoder.hpp"
#include "Resource.hpp"
#include "Types.hpp"

namespace mtl
{
    enum class IndirectCommandType: ns::UInteger
    {
        MTLIndirectCommandTypeDraw                = (1 << 0),
        MTLIndirectCommandTypeDrawIndexed         = (1 << 1),
        MTLIndirectCommandTypeDrawPatches         API_AVAILABLE(tvos(14.5)) = (1 << 2),
        MTLIndirectCommandTypeDrawIndexedPatches  API_AVAILABLE(tvos(14.5)) = (1 << 3) ,

        MTLIndirectCommandTypeConcurrentDispatch  API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(13.0)) = (1 << 5), /* Dispatch threadgroups with concurrent execution */

        MTLIndirectCommandTypeConcurrentDispatchThreads  API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(13.0)) = (1 << 6), /* Dispatch threads with concurrent execution */
    } API_AVAILABLE(macos(10.14), ios(12.0));

    [[nodiscard]] inline constexpr IndirectCommandType operator&(const IndirectCommandType a, const IndirectCommandType b) noexcept
    {
        return static_cast<IndirectCommandType>(static_cast<std::underlying_type_t<IndirectCommandType>>(a) & static_cast<std::underlying_type_t<IndirectCommandType>>(b));
    }
    [[nodiscard]] inline constexpr IndirectCommandType operator|(const IndirectCommandType a, const IndirectCommandType b) noexcept
    {
        return static_cast<IndirectCommandType>(static_cast<std::underlying_type_t<IndirectCommandType>>(a) | static_cast<std::underlying_type_t<IndirectCommandType>>(b));
    }
    [[nodiscard]] inline constexpr IndirectCommandType operator^(const IndirectCommandType a, const IndirectCommandType b) noexcept
    {
        return static_cast<IndirectCommandType>(static_cast<std::underlying_type_t<IndirectCommandType>>(a) ^ static_cast<std::underlying_type_t<IndirectCommandType>>(b));
    }
    [[nodiscard]] inline constexpr IndirectCommandType operator~(const IndirectCommandType a) noexcept
    {
        return static_cast<IndirectCommandType>(~static_cast<std::underlying_type_t<IndirectCommandType>>(a));
    }
    inline constexpr IndirectCommandType& operator&=(IndirectCommandType& a, const IndirectCommandType b) noexcept
    {
        return a = static_cast<IndirectCommandType>(static_cast<std::underlying_type_t<IndirectCommandType>>(a) & static_cast<std::underlying_type_t<IndirectCommandType>>(b));
    }
    inline constexpr IndirectCommandType& operator|=(IndirectCommandType& a, const IndirectCommandType b) noexcept
    {
        return a = static_cast<IndirectCommandType>(static_cast<std::underlying_type_t<IndirectCommandType>>(a) | static_cast<std::underlying_type_t<IndirectCommandType>>(b));
    }
    inline constexpr IndirectCommandType& operator^=(IndirectCommandType& a, const IndirectCommandType b) noexcept
    {
        return a = static_cast<IndirectCommandType>(static_cast<std::underlying_type_t<IndirectCommandType>>(a) ^ static_cast<std::underlying_type_t<IndirectCommandType>>(b));
    }

    struct IndirectCommandBufferExecutionRange final
    {
        std::uint32_t location;
        std::uint32_t length;
    } API_AVAILABLE(macos(10.14), macCatalyst(13.0), ios(13.0));

    class IndirectCommandBufferDescriptor: public ns::Object, public ns::Copying
    {
    public:
        METALPP_PRIVATE_CLS("MTLIndirectCommandBufferDescriptor");

        METALPP_PRIVATE_SEL(commandTypes, "commandTypes");
        METALPP_PRIVATE_SEL(setCommandTypes_, "setCommandTypes:");
        METALPP_PRIVATE_SEL(inheritPipelineState, "inheritPipelineState");
        METALPP_PRIVATE_SEL(setInheritPipelineState_, "setInheritPipelineState:");
        METALPP_PRIVATE_SEL(inheritBuffers, "inheritBuffers");
        METALPP_PRIVATE_SEL(setInheritBuffers_, "setInheritBuffers:");
        METALPP_PRIVATE_SEL(maxVertexBufferBindCount, "maxVertexBufferBindCount");
        METALPP_PRIVATE_SEL(setMaxVertexBufferBindCount_, "setMaxVertexBufferBindCount:");
        METALPP_PRIVATE_SEL(maxFragmentBufferBindCount, "maxFragmentBufferBindCount");
        METALPP_PRIVATE_SEL(setMaxFragmentBufferBindCount_, "setMaxFragmentBufferBindCount:");
        METALPP_PRIVATE_SEL(maxKernelBufferBindCount, "maxKernelBufferBindCount");
        METALPP_PRIVATE_SEL(setMaxKernelBufferBindCount_, "setMaxKernelBufferBindCount:");
        METALPP_PRIVATE_SEL(supportRayTracing, "supportRayTracing");
        METALPP_PRIVATE_SEL(setSupportRayTracing_, "setSupportRayTracing:");

        using Object::Object;
        using Object::operator=;

        IndirectCommandBufferDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto commandTypes() const noexcept
        {
            return sendMessage<IndirectCommandType>(METALPP_SEL(commandTypes));
        }

        void setCommandTypes(const IndirectCommandType commandTypes) noexcept
        {
            sendMessage(METALPP_SEL(setCommandTypes_), commandTypes);
        }

        [[nodiscard]] auto inheritPipelineState() const noexcept API_AVAILABLE(macos(10.14), ios(13.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(inheritPipelineState)) == YES;
        }

        void setInheritPipelineState(const bool inheritPipelineState) noexcept API_AVAILABLE(macos(10.14), ios(13.0))
        {
            sendMessage(METALPP_SEL(setInheritPipelineState_), inheritPipelineState ? YES : NO);
        }

        [[nodiscard]] auto inheritBuffers() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(inheritBuffers)) == YES;
        }

        void setInheritBuffers(const bool inheritBuffers) noexcept
        {
            sendMessage(METALPP_SEL(setInheritBuffers_), inheritBuffers ? YES : NO);
        }

        [[nodiscard]] auto maxVertexBufferBindCount() const noexcept API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(13.0))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxVertexBufferBindCount));
        }

        void setMaxVertexBufferBindCount(const ns::UInteger maxVertexBufferBindCount) noexcept API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(13.0))
        {
            sendMessage(METALPP_SEL(setMaxVertexBufferBindCount_), maxVertexBufferBindCount);
        }

        [[nodiscard]] auto maxFragmentBufferBindCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxFragmentBufferBindCount));
        }

        void setMaxFragmentBufferBindCount(const ns::UInteger maxFragmentBufferBindCount) noexcept
        {
            sendMessage(METALPP_SEL(setMaxFragmentBufferBindCount_), maxFragmentBufferBindCount);
        }

        [[nodiscard]] auto maxKernelBufferBindCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxKernelBufferBindCount));
        }

        void setMaxKernelBufferBindCount(const ns::UInteger maxKernelBufferBindCount) noexcept
        {
            sendMessage(METALPP_SEL(setMaxKernelBufferBindCount_), maxKernelBufferBindCount);
        }

        [[nodiscard]] auto supportRayTracing() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportRayTracing)) == YES;
        }

        void setSupportRayTracing(const bool supportRayTracing) noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            sendMessage(METALPP_SEL(setSupportRayTracing_), supportRayTracing ? YES : NO);
        }
    } API_AVAILABLE(macos(10.14), ios(12.0));

    class IndirectCommandBuffer: public Resource
    {
    public:
        METALPP_PRIVATE_SEL(size, "size");
        METALPP_PRIVATE_SEL(gpuResourceID, "gpuResourceID");
        METALPP_PRIVATE_SEL(resetWithRange_, "resetWithRange:");

        [[nodiscard]] auto size() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(size));
        }

        [[nodiscard]] auto gpuResourceID() const noexcept
        {
            return sendMessage<ResourceID>(METALPP_SEL(gpuResourceID));
        }

        void resetWithRange(const ns::Range range) noexcept
        {
            sendMessage(METALPP_SEL(resetWithRange_), range);
        }
    };
}

#endif
