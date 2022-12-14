#ifndef METALPP_QUARTZCORE_METALLAYER_HPP
#define METALPP_QUARTZCORE_METALLAYER_HPP

#include "../objc/Private.hpp"
#include "../metal/Device.hpp"
#include "../metal/Drawable.hpp"
#include "../metal/Texture.hpp"
#include "Layer.hpp"

namespace ca
{
    class MetalLayer;

    class MetalDrawable: public mtl::Drawable
    {
    public:
        METALPP_PRIVATE_SEL(texture, "texture");
        METALPP_PRIVATE_SEL(layer, "layer");

        using Drawable::Drawable;
        using Drawable::operator=;

        MetalDrawable() = delete;

        [[nodiscard]] auto texture() const noexcept
        {
            return mtl::Texture{sendMessage<id>(METALPP_SEL(texture))};
        }

        [[nodiscard]] MetalLayer layer() const noexcept;
    };

    class MetalLayer final: public Layer
    {
    public:
        METALPP_PRIVATE_CLS("CAMetalLayer");

        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(setDevice_, "setDevice:");
        METALPP_PRIVATE_SEL(pixelFormat, "pixelFormat");
        METALPP_PRIVATE_SEL(setPixelFormat_, "setPixelFormat:");
        METALPP_PRIVATE_SEL(framebufferOnly, "framebufferOnly");
        METALPP_PRIVATE_SEL(setFramebufferOnly_, "setFramebufferOnly:");
        METALPP_PRIVATE_SEL(drawableSize, "drawableSize");
        METALPP_PRIVATE_SEL(setDrawableSize_, "setDrawableSize:");
        METALPP_PRIVATE_SEL(nextDrawable, "nextDrawable");
        METALPP_PRIVATE_SEL(presentsWithTransaction, "presentsWithTransaction");
        METALPP_PRIVATE_SEL(setPresentsWithTransaction_, "setPresentsWithTransaction:");

        using Layer::Layer;
        using Layer::operator=;
        
        MetalLayer() noexcept:
            Layer{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto device() const noexcept
        {
            return mtl::Device{sendMessage<id>(METALPP_SEL(device))};
        }

        void setDevice(const mtl::Device& device) noexcept
        {
            sendMessage(METALPP_SEL(setDevice_), device.get());
        }

        [[nodiscard]] auto pixelFormat() const noexcept
        {
            return sendMessage<mtl::PixelFormat>(METALPP_SEL(pixelFormat));
        }

        void setPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            sendMessage(METALPP_SEL(setPixelFormat_), pixelFormat);
        }

        [[nodiscard]] auto framebufferOnly() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(framebufferOnly)) == YES;
        }

        void setFramebufferOnly(const bool framebufferOnly) noexcept
        {
            sendMessage(METALPP_SEL(setFramebufferOnly_), framebufferOnly ? YES : NO);
        }

        [[nodiscard]] auto drawableSize() const noexcept
        {
            return sendMessage<cg::Size>(METALPP_SEL(drawableSize));
        }

        void setDrawableSize(const cg::Size& drawableSize) noexcept
        {
            sendMessage(METALPP_SEL(setDrawableSize_), drawableSize);
        }

        auto nextDrawable() noexcept
        {
            return MetalDrawable{sendMessage<id>(METALPP_SEL(nextDrawable))};
        }

        [[nodiscard]] auto presentsWithTransaction() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(presentsWithTransaction)) == YES;
        }

        void setPresentsWithTransaction(const bool presentsWithTransaction) noexcept
        {
            sendMessage(METALPP_SEL(setPresentsWithTransaction_), presentsWithTransaction ? YES : NO);
        }
    };

    [[nodiscard]] inline MetalLayer MetalDrawable::layer() const noexcept
    {
        return MetalLayer{sendMessage<id>(METALPP_SEL(layer))};
    }
}

#endif
