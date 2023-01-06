#ifndef METALPP_METAL_BLITCOMMANDENCODER_HPP
#define METALPP_METAL_BLITCOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "../foundation/Range.hpp"
#include "CommandEncoder.hpp"
#include "Buffer.hpp"
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

    class BlitCommandEncoder final: public CommandEncoder
    {
    public:
        METALPP_PRIVATE_SEL(copyFromTexture_sourceSlice_sourceLevel_sourceOrigin_sourceSize_toTexture_destinationSlice_destinationLevel_destinationOrigin_, "copyFromTexture:sourceSlice:sourceLevel:sourceOrigin:sourceSize:toTexture:destinationSlice:destinationLevel:destinationOrigin:");
        METALPP_PRIVATE_SEL(generateMipmapsForTexture_, "generateMipmapsForTexture:");
        METALPP_PRIVATE_SEL(fillBuffer_range_value_, "fillBuffer:range:value:");
        METALPP_PRIVATE_SEL(copyFromBuffer_sourceOffset_toBuffer_destinationOffset_size_, "copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:");
        
        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        BlitCommandEncoder() = delete;

        void copyTexture(const Texture& sourceTexture,
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

        void generateMipmapsForTexture(const Texture& texture) noexcept
        {
            sendMessage(METALPP_SEL(generateMipmapsForTexture_), texture.get());
        }

        void fillBuffer(const Buffer& buffer, const ns::Range& range, std::uint8_t value) noexcept
        {
            sendMessage(METALPP_SEL(fillBuffer_range_value_), buffer.get(), range, value);
        }

        void copyBuffer(const Buffer& sourceBuffer,
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
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
