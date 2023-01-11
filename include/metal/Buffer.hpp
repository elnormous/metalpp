#ifndef METALPP_METAL_BUFFER_HPP
#define METALPP_METAL_BUFFER_HPP

#include <os/availability.h>
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Range.hpp"
#include "Resource.hpp"

namespace mtl
{
    class Texture;
    class TextureDescriptor;

    class Buffer: public Resource
    {
    public:
        METALPP_PRIVATE_SEL(length, "length");
        METALPP_PRIVATE_SEL(contents, "contents");
        METALPP_PRIVATE_SEL(didModifyRange_, "didModifyRange:");
        METALPP_PRIVATE_SEL(newTextureWithDescriptor_offset_bytesPerRow_, "newTextureWithDescriptor:offset:bytesPerRow:");
        METALPP_PRIVATE_SEL(gpuAddress, "gpuAddress");

        using Resource::Resource;
        using Resource::operator=;

        Buffer() = delete;

        [[nodiscard]] auto length() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(length));
        }

        [[nodiscard]] auto contents() const noexcept
        {
            return sendMessage<void*>(METALPP_SEL(contents));
        }

        void didModifyRange(const ns::Range& range) const noexcept API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios)
        {
            sendMessage(METALPP_SEL(didModifyRange_), range);
        }

        Texture newTexture(const TextureDescriptor& descriptor, const ns::UInteger offset, const ns::UInteger bytesPerRow) API_AVAILABLE(macos(10.13), ios(8.0));

        [[nodiscard]] auto gpuAddress() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<uint64_t>(METALPP_SEL(gpuAddress));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
