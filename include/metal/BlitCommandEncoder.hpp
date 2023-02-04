#ifndef METALPP_METAL_BLITCOMMANDENCODER_HPP
#define METALPP_METAL_BLITCOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "../foundation/Range.hpp"
#include "CommandEncoder.hpp"
#include "Buffer.hpp"
#include "Fence.hpp"
#include "Resource.hpp"
#include "Texture.hpp"
#include "Types.hpp"

namespace mtl
{
    enum class BlitOption: ns::UInteger
    {
        None                       = 0,
        DepthFromDepthStencil      = 1 << 0,
        StencilFromDepthStencil    = 1 << 1,
        RowLinearPVRTC API_AVAILABLE(ios(9.0), macos(11.0), macCatalyst(14.0)) = 1 << 2,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    [[nodiscard]] inline constexpr BlitOption operator&(const BlitOption a, const BlitOption b) noexcept
    {
        return static_cast<BlitOption>(static_cast<std::underlying_type_t<BlitOption>>(a) & static_cast<std::underlying_type_t<BlitOption>>(b));
    }
    [[nodiscard]] inline constexpr BlitOption operator|(const BlitOption a, const BlitOption b) noexcept
    {
        return static_cast<BlitOption>(static_cast<std::underlying_type_t<BlitOption>>(a) | static_cast<std::underlying_type_t<BlitOption>>(b));
    }
    [[nodiscard]] inline constexpr BlitOption operator^(const BlitOption a, const BlitOption b) noexcept
    {
        return static_cast<BlitOption>(static_cast<std::underlying_type_t<BlitOption>>(a) ^ static_cast<std::underlying_type_t<BlitOption>>(b));
    }
    [[nodiscard]] inline constexpr BlitOption operator~(const BlitOption a) noexcept
    {
        return static_cast<BlitOption>(~static_cast<std::underlying_type_t<BlitOption>>(a));
    }
    inline constexpr BlitOption& operator&=(BlitOption& a, const BlitOption b) noexcept
    {
        return a = static_cast<BlitOption>(static_cast<std::underlying_type_t<BlitOption>>(a) & static_cast<std::underlying_type_t<BlitOption>>(b));
    }
    inline constexpr BlitOption& operator|=(BlitOption& a, const BlitOption b) noexcept
    {
        return a = static_cast<BlitOption>(static_cast<std::underlying_type_t<BlitOption>>(a) | static_cast<std::underlying_type_t<BlitOption>>(b));
    }
    inline constexpr BlitOption& operator^=(BlitOption& a, const BlitOption b) noexcept
    {
        return a = static_cast<BlitOption>(static_cast<std::underlying_type_t<BlitOption>>(a) ^ static_cast<std::underlying_type_t<BlitOption>>(b));
    }

    class BlitCommandEncoder final: public CommandEncoder
    {
    public:
        METALPP_PRIVATE_SEL(synchronizeResource_, "synchronizeResource:");
        METALPP_PRIVATE_SEL(synchronizeTexture_slice_level_, "synchronizeTexture:slice:level:");
        METALPP_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_, "copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:");
        METALPP_PRIVATE_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_, "copyFromBuffer:sourceOffset:sourceBytesPerRow:sourceBytesPerImage:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:");
        METALPP_PRIVATE_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_options_, "copyFromBuffer:sourceOffset:sourceBytesPerRow:sourceBytesPerImage:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:options:");
        METALPP_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_, "copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toBuffer:destinationOffset:destinationBytesPerRow:destinationBytesPerImage:");
        METALPP_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_options_, "copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toBuffer:destinationOffset:destinationBytesPerRow:destinationBytesPerImage:options:");
        METALPP_PRIVATE_SEL(generateMipmapsForTexture_, "generateMipmapsForTexture:");
        METALPP_PRIVATE_SEL(fillBuffer_range_value_, "fillBuffer:range:value:");
        METALPP_PRIVATE_SEL(copyFromTexture_toTexture_, "copyFromTexture:toTexture:");
        METALPP_PRIVATE_SEL(copyFromBuffer_sourceOffset_toBuffer_destinationOffset_size_, "copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:");
        METALPP_PRIVATE_SEL(updateFence_, "updateFence:");
        METALPP_PRIVATE_SEL(waitForFence_, "waitForFence:");
        METALPP_PRIVATE_SEL(optimizeContentsForGPUAccess_, "optimizeContentsForGPUAccess:");
        METALPP_PRIVATE_SEL(optimizeContentsForGPUAccess_slice_level_, "optimizeContentsForGPUAccess:slice:level:");
        METALPP_PRIVATE_SEL(optimizeContentsForCPUAccess_, "optimizeContentsForCPUAccess:");
        METALPP_PRIVATE_SEL(optimizeContentsForCPUAccess_slice_level_, "optimizeContentsForCPUAccess:slice:level:");

        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        BlitCommandEncoder() = delete;

        void synchronizeResource(const Resource& resource) noexcept API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios)
        {
            sendMessage(METALPP_SEL(synchronizeResource_), resource.get());
        }

        void synchronizeTexture(const Texture& texture, const ns::UInteger slice, const ns::UInteger level) API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios)
        {
            sendMessage(METALPP_SEL(synchronizeTexture_slice_level_), texture.get(), slice, level);
        }

        void copyFromTexture(const Texture& sourceTexture,
                             const ns::UInteger sourceSlice,
                             const ns::UInteger sourceLevel,
                             const Origin& sourceOrigin,
                             const Size& sourceSize,
                             const Texture& destinationTexture,
                             const ns::UInteger destinationSlice,
                             const ns::UInteger destinationLevel,
                             const Origin& destinationOrigin) noexcept
        {
            sendMessage(METALPP_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_),
                        sourceTexture.get(),
                        sourceSlice,
                        sourceLevel,
                        sourceOrigin,
                        sourceSize,
                        destinationTexture.get(),
                        destinationSlice,
                        destinationLevel,
                        destinationOrigin);
        }

        void copyFromBuffer(const Buffer& sourceBuffer,
                            const ns::UInteger sourceOffset,
                            const ns::UInteger sourceBytesPerRow,
                            const ns::UInteger sourceBytesPerImage,
                            const Size& sourceSize,
                            const Texture& destinationTexture,
                            const ns::UInteger destinationSlice,
                            const ns::UInteger destinationLevel,
                            const Origin& destinationOrigin)
        {
            sendMessage(METALPP_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_),
                        sourceBuffer.get(),
                        sourceOffset,
                        sourceBytesPerRow,
                        sourceBytesPerImage,
                        sourceSize,
                        destinationTexture.get(),
                        destinationSlice,
                        destinationLevel,
                        destinationOrigin);
        }

        void copyFromBuffer(const Buffer& sourceBuffer,
                            const ns::UInteger sourceOffset,
                            const ns::UInteger sourceBytesPerRow,
                            const ns::UInteger sourceBytesPerImage,
                            const Size& sourceSize,
                            const Texture& destinationTexture,
                            const ns::UInteger destinationSlice,
                            const ns::UInteger destinationLevel,
                            const Origin& destinationOrigin,
                            const BlitOption options)
        {
            sendMessage(METALPP_SEL(copyFromBuffer_sourceOffset_sourceBytesPerRow_sourceBytesPerImage_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_),
                        sourceBuffer.get(),
                        sourceOffset,
                        sourceBytesPerRow,
                        sourceBytesPerImage,
                        sourceSize,
                        destinationTexture.get(),
                        destinationSlice,
                        destinationLevel,
                        destinationOrigin,
                        options);
        }

        void copyFromTexture(const Texture& sourceTexture,
                             const ns::UInteger sourceSlice,
                             const ns::UInteger sourceLevel,
                             const Origin& sourceOrigin,
                             const Size& sourceSize,
                             const Buffer& destinationBuffer,
                             const ns::UInteger destinationOffset,
                             const ns::UInteger destinationBytesPerRow,
                             const ns::UInteger& destinationBytesPerImage) noexcept
        {
            sendMessage(METALPP_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_),
                        sourceTexture.get(),
                        sourceSlice,
                        sourceLevel,
                        sourceOrigin,
                        sourceSize,
                        destinationBuffer.get(),
                        destinationOffset,
                        destinationBytesPerRow,
                        destinationBytesPerImage);
        }

        void copyFromTexture(const Texture& sourceTexture,
                             const ns::UInteger sourceSlice,
                             const ns::UInteger sourceLevel,
                             const Origin& sourceOrigin,
                             const Size& sourceSize,
                             const Buffer& destinationBuffer,
                             const ns::UInteger destinationOffset,
                             const ns::UInteger destinationBytesPerRow,
                             const ns::UInteger& destinationBytesPerImage,
                             const BlitOption options) noexcept
        {
            sendMessage(METALPP_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toBuffer_destinationOffset_destinationBytesPerRow_destinationBytesPerImage_),
                        sourceTexture.get(),
                        sourceSlice,
                        sourceLevel,
                        sourceOrigin,
                        sourceSize,
                        destinationBuffer.get(),
                        destinationOffset,
                        destinationBytesPerRow,
                        destinationBytesPerImage,
                        options);
        }

        void generateMipmapsForTexture(const Texture& texture) noexcept
        {
            sendMessage(METALPP_SEL(generateMipmapsForTexture_), texture.get());
        }

        void fillBuffer(const Buffer& buffer,
                        const ns::Range& range,
                        const std::uint8_t value) noexcept
        {
            sendMessage(METALPP_SEL(fillBuffer_range_value_), buffer.get(), range, value);
        }

        void copyFromTexture(const Texture& sourceTexture, const Texture& destinationTexture) API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(copyFromTexture_toTexture_), sourceTexture.get(), destinationTexture.get());
        }

        void copyFromBuffer(const Buffer& sourceBuffer,
                            const ns::UInteger sourceOffset,
                            const Buffer& destinationBuffer,
                            const ns::UInteger destinationOffset,
                            const ns::UInteger size) noexcept
        {
            sendMessage(METALPP_SEL(copyFromBuffer_sourceOffset_toBuffer_destinationOffset_size_),
                        sourceBuffer.get(),
                        sourceOffset,
                        destinationBuffer.get(),
                        destinationOffset,
                        size);
        }

        void updateFence(const Fence& fence) noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            sendMessage(METALPP_SEL(updateFence_), fence.get());
        }

        void waitForFence(const Fence& fence) noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            sendMessage(METALPP_SEL(waitForFence_), fence.get());
        }

        void optimizeContentsForGPUAccess(const Texture& texture) noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            sendMessage(METALPP_SEL(optimizeContentsForGPUAccess_), texture.get());
        }

        void optimizeContentsForGPUAccess(const Texture& texture, const ns::UInteger slice, const ns::UInteger level) noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            sendMessage(METALPP_SEL(optimizeContentsForGPUAccess_slice_level_), texture.get(), slice, level);
        }

        void optimizeContentsForCPUAccess(const Texture& texture) noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            sendMessage(METALPP_SEL(optimizeContentsForCPUAccess_), texture.get());
        }

        void optimizeContentsForCPUAccess(const Texture& texture, const ns::UInteger slice, const ns::UInteger level) noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            sendMessage(METALPP_SEL(optimizeContentsForCPUAccess_slice_level_), texture.get(), slice, level);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
