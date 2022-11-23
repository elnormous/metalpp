#ifndef METALPP_QUARTZCORE_METALLAYER_HPP
#define METALPP_QUARTZCORE_METALLAYER_HPP

#include "../metal/Drawable.hpp"
#include "../metal/Texture.hpp"
#include "Device.hpp"
#include "Layer.hpp"
#include "Selectors.hpp"

namespace ca
{
    class MetalDrawable: public mtl::Drawable
    {
        MetalDrawable() = delete;
    };

    class MetalLayer final: public Layer
    {
        static inline const auto cls = objc_lookUpClass("CAMetalLayer");
    public:
        MetalLayer() noexcept:
            Layer{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] auto device() const noexcept
        {
            return getRetained<mtl::Device>(mtl::sel::device);
        }

        void setDevice(const mtl::Device& device) noexcept
        {
            sendMessage(mtl::sel::setDevice_, static_cast<id>(device));
        }

        [[nodiscard]] auto pixelFormat() const noexcept
        {
            return sendMessage<mtl::PixelFormat>(sel::pixelFormat);
        }

        void setPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            sendMessage(sel::setPixelFormat_, pixelFormat);
        }

        [[nodiscard]] auto framebufferOnly() const noexcept
        {
            return sendMessage<BOOL>(sel::framebufferOnly) == YES;
        }

        void setFramebufferOnly(const bool framebufferOnly) noexcept
        {
            sendMessage(sel::setFramebufferOnly_, framebufferOnly ? YES : NO);
        }

        [[nodiscard]] auto drawableSize() const noexcept
        {
            return sendMessage<cg::Size>(sel::drawableSize);
        }

        void setDrawableSize(const cg::Size& drawableSize) noexcept
        {
            sendMessage(sel::setDrawableSize_, drawableSize);
        }

        auto nextDrawable() noexcept
        {
            return getRetained<MetalDrawable>(sel::nextDrawable);
        }

        [[nodiscard]] auto presentsWithTransaction() const noexcept
        {
            return sendMessage<BOOL>(sel::presentsWithTransaction) == YES;
        }

        void setPresentsWithTransaction(const bool presentsWithTransaction) noexcept
        {
            sendMessage(sel::setPresentsWithTransaction_, presentsWithTransaction ? YES : NO);
        }
    };
}

#endif
