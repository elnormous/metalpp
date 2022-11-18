#ifndef METALPP_METAL_RENDERPASS_HPP
#define METALPP_METAL_RENDERPASS_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "Texture.hpp"
#include "Selectors.hpp"

namespace mtl
{
    struct ClearColor
    {
        ClearColor() noexcept = default;
        ClearColor(double r, double g, double b, double a) noexcept: red{r}, green{g}, blue{b}, alpha{a} {}

        bool operator==(const ClearColor& other) const noexcept
        {
            return other.red == red && other.green == green && other.blue == blue && other.alpha == alpha;
        }

        bool operator!=(const ClearColor& other) const noexcept
        {
            return other.red != red || other.green != green || other.blue != blue || other.alpha != alpha;
        }

        double red = 0.0;
        double green = 0.0;
        double blue = 0.0;
        double alpha = 0.0;
    };

    enum class LoadAction: NSUInteger
    {
        DontCare = 0,
        Load = 1,
        Clear = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StoreAction: NSUInteger
    {
        DontCare = 0,
        Store = 1,
        MultisampleResolve = 2,
        StoreAndMultisampleResolve API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
        Unknown API_AVAILABLE(macos(10.12), ios(10.0)) = 4,
        CustomSampleDepthStore API_AVAILABLE(macos(10.13), ios(11.0)) = 5,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StoreActionOptions: NSUInteger
    {
        None                  = 0,
        CustomSamplePositions = 1 << 0,
    } API_AVAILABLE(macos(10.13), ios(11.0));

    class RenderPassAttachmentDescriptor: public ns::Object
    {
    public:
        RenderPassAttachmentDescriptor() = delete;

        [[nodiscard]] Texture texture() const noexcept
        {
            const id texture = objc::sendMessage<id>(*this, sel::texture);
            return Texture{objc::sendMessage<id>(texture, ns::sel::retain)};
        }

        void setTexture(const Texture& texture) noexcept
        {
            objc::sendMessage(*this, sel::setTexture_, static_cast<id>(texture));
        }

        [[nodiscard]] NSUInteger level() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::level);
        }

        void setLevel(NSUInteger level) noexcept
        {
            objc::sendMessage(*this, sel::setLevel_, level);
        }

        [[nodiscard]] NSUInteger slice() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::slice);
        }

        void setSlice(NSUInteger slice) noexcept
        {
            objc::sendMessage(*this, sel::setSlice_, slice);
        }

        [[nodiscard]] NSUInteger depthPlane() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::depthPlane);
        }

        void setDepthPlane(NSUInteger depthPlane) noexcept
        {
            objc::sendMessage(*this, sel::setDepthPlane_, depthPlane);
        }

        [[nodiscard]] Texture resolveTexture() const noexcept
        {
            const id resolveTexture = objc::sendMessage<id>(*this, sel::resolveTexture);
            return Texture{objc::sendMessage<id>(resolveTexture, ns::sel::retain)};
        }

        void setResolveTexture(const Texture& resolveTexture) noexcept
        {
            objc::sendMessage(*this, sel::setResolveTexture_, static_cast<id>(resolveTexture));
        }

        [[nodiscard]] NSUInteger resolveLevel() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::resolveLevel);
        }

        void setResolveLevel(NSUInteger resolveLevel) noexcept
        {
            objc::sendMessage(*this, sel::setResolveLevel_, resolveLevel);
        }

        [[nodiscard]] NSUInteger resolveSlice() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::resolveSlice);
        }

        void setResolveSlice(NSUInteger resolveSlice) noexcept
        {
            objc::sendMessage(*this, sel::setResolveSlice_, resolveSlice);
        }

        [[nodiscard]] NSUInteger resolveDepthPlane() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::resolveDepthPlane);
        }

        void setResolveDepthPlane(NSUInteger resolveDepthPlane) noexcept
        {
            objc::sendMessage(*this, sel::setResolveDepthPlane_, resolveDepthPlane);
        }

        [[nodiscard]] LoadAction loadAction() const noexcept
        {
            return objc::sendMessage<LoadAction>(*this, sel::loadAction);
        }

        void setLoadAction(LoadAction loadAction) noexcept
        {
            objc::sendMessage(*this, sel::setLoadAction_, loadAction);
        }

        [[nodiscard]] StoreAction storeAction() const noexcept
        {
            return objc::sendMessage<StoreAction>(*this, sel::storeAction);
        }

        void setStoreAction(StoreAction storeAction) noexcept
        {
            objc::sendMessage(*this, sel::setStoreAction_, storeAction);
        }

        [[nodiscard]] StoreActionOptions storeActionOptions() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return objc::sendMessage<StoreActionOptions>(*this, sel::storeActionOptions);
        }

        void setStoreActionOptions(StoreActionOptions storeActionOptions) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            objc::sendMessage(*this, sel::setStoreActionOptions_, storeActionOptions);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassColorAttachmentDescriptor final: public RenderPassAttachmentDescriptor
    {
    public:
        [[nodiscard]] ClearColor clearColor() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return objc::sendMessage<ClearColor>(*this, sel::clearColor);
        }

        void setClearColor(ClearColor clearColor) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            objc::sendMessage(*this, sel::setClearColor_, clearColor);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class MultisampleDepthResolveFilter: NSUInteger
    {
        Sample0 = 0,
        Min = 1,
        Max = 2,
    } API_AVAILABLE(macos(10.14), ios(9.0));

    class RenderPassDepthAttachmentDescriptor final: public ns::Object
    {
    public:
        [[nodiscard]] double clearDepth() const noexcept
        {
            return objc::sendMessage<double>(*this, sel::clearDepth);
        }

        void setClearDepth(double clearDepth) noexcept
        {
            objc::sendMessage(*this, sel::setClearDepth_, clearDepth);
        }

        [[nodiscard]] MultisampleDepthResolveFilter depthResolveFilter() const noexcept API_AVAILABLE(macos(10.14), ios(9.0))
        {
            return objc::sendMessage<MultisampleDepthResolveFilter>(*this, sel::depthResolveFilter);
        }

        void setDepthResolveFilter(MultisampleDepthResolveFilter depthResolveFilter) noexcept API_AVAILABLE(macos(10.14), ios(9.0))
        {
            objc::sendMessage(*this, sel::setDepthResolveFilter_, depthResolveFilter);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class MultisampleStencilResolveFilter: NSUInteger
    {
        Sample0               = 0,
        DepthResolvedSample   = 1,
    } API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5));

    class RenderPassStencilAttachmentDescriptor final: public ns::Object
    {
    public:
        [[nodiscard]] uint32_t clearStencil() const noexcept
        {
            return objc::sendMessage<uint32_t>(*this, sel::clearStencil);
        }

        void setClearStencil(uint32_t clearStencil) noexcept
        {
            objc::sendMessage(*this, sel::setClearStencil_, clearStencil);
        }

        [[nodiscard]] MultisampleStencilResolveFilter stencilResolveFilter() const noexcept API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
        {
            return objc::sendMessage<MultisampleStencilResolveFilter>(*this, sel::stencilResolveFilter);
        }

        void setStencilResolveFilter(MultisampleStencilResolveFilter stencilResolveFilter) noexcept API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
        {
            objc::sendMessage(*this, sel::setStencilResolveFilter_, stencilResolveFilter);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassColorAttachmentDescriptorArray final: public ns::Object
    {
    public:
        [[nodiscard]] RenderPassColorAttachmentDescriptor operator[](const std::size_t index) const noexcept
        {
            return objectAtIndexedSubscript(static_cast<NSUInteger>(index));
        }

        [[nodiscard]] RenderPassColorAttachmentDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndexedSubscript_,
                                                    index);
            return RenderPassColorAttachmentDescriptor{objc::sendMessage<id>(object, ns::sel::retain)};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassDescriptor final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLRenderPassDescriptor");
    public:
        RenderPassDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] RenderPassColorAttachmentDescriptorArray colorAttachments() const noexcept
        {
            const id colorAttachments = objc::sendMessage<id>(*this,
                                                              sel::colorAttachments);
            return RenderPassColorAttachmentDescriptorArray{objc::sendMessage<id>(colorAttachments, ns::sel::retain)};
        }

        [[nodiscard]] RenderPassDepthAttachmentDescriptor depthAttachment() const noexcept
        {
            const id depthAttachment = objc::sendMessage<id>(*this,
                                                             sel::depthAttachment);
            return RenderPassDepthAttachmentDescriptor{objc::sendMessage<id>(depthAttachment, ns::sel::retain)};
        }

        [[nodiscard]] RenderPassStencilAttachmentDescriptor stencilAttachment() const noexcept
        {
            const id stencilAttachment = objc::sendMessage<id>(*this,
                                                               sel::stencilAttachment);
            return RenderPassStencilAttachmentDescriptor{objc::sendMessage<id>(stencilAttachment, ns::sel::retain)};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
