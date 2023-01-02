#ifndef METALPP_METAL_BLITCOMMANDENCODER_HPP
#define METALPP_METAL_BLITCOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "../foundation/Range.hpp"
#include "CommandEncoder.hpp"
#include "Buffer.hpp"
#include "Texture.hpp"

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
        METALPP_PRIVATE_SEL(generateMipmapsForTexture_, "generateMipmapsForTexture:");
        METALPP_PRIVATE_SEL(fillBuffer_range_value_, "fillBuffer:range:value:");
        
        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        BlitCommandEncoder() = delete;

        void generateMipmapsForTexture(const Texture& texture) noexcept
        {
            sendMessage(METALPP_SEL(generateMipmapsForTexture_), texture.get());
        }

        void fillBuffer(const Buffer& buffer, const ns::Range& range, std::uint8_t value) noexcept
        {
            sendMessage(METALPP_SEL(fillBuffer_range_value_), buffer.get(), range, value);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
