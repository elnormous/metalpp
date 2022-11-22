#ifndef METALPP_METAL_RENDERPASS_HPP
#define METALPP_METAL_RENDERPASS_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "Texture.hpp"
#include "Selectors.hpp"

namespace mtl
{
    struct ClearColor final
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

    enum class LoadAction: ns::UInteger
    {
        DontCare = 0,
        Load = 1,
        Clear = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StoreAction: ns::UInteger
    {
        DontCare = 0,
        Store = 1,
        MultisampleResolve = 2,
        StoreAndMultisampleResolve API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
        Unknown API_AVAILABLE(macos(10.12), ios(10.0)) = 4,
        CustomSampleDepthStore API_AVAILABLE(macos(10.13), ios(11.0)) = 5,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StoreActionOptions: ns::UInteger
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
            return getRetained<Texture>(sel::texture);
        }

        void setTexture(const Texture& texture) noexcept
        {
            sendMessage(sel::setTexture_, static_cast<id>(texture));
        }

        [[nodiscard]] ns::UInteger level() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::level);
        }

        void setLevel(ns::UInteger level) noexcept
        {
            sendMessage(sel::setLevel_, level);
        }

        [[nodiscard]] ns::UInteger slice() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::slice);
        }

        void setSlice(ns::UInteger slice) noexcept
        {
            sendMessage(sel::setSlice_, slice);
        }

        [[nodiscard]] ns::UInteger depthPlane() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::depthPlane);
        }

        void setDepthPlane(ns::UInteger depthPlane) noexcept
        {
            sendMessage(sel::setDepthPlane_, depthPlane);
        }

        [[nodiscard]] Texture resolveTexture() const noexcept
        {
            return getRetained<Texture>(sel::resolveTexture);
        }

        void setResolveTexture(const Texture& resolveTexture) noexcept
        {
            sendMessage(sel::setResolveTexture_, static_cast<id>(resolveTexture));
        }

        [[nodiscard]] ns::UInteger resolveLevel() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::resolveLevel);
        }

        void setResolveLevel(ns::UInteger resolveLevel) noexcept
        {
            sendMessage(sel::setResolveLevel_, resolveLevel);
        }

        [[nodiscard]] ns::UInteger resolveSlice() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::resolveSlice);
        }

        void setResolveSlice(ns::UInteger resolveSlice) noexcept
        {
            sendMessage(sel::setResolveSlice_, resolveSlice);
        }

        [[nodiscard]] ns::UInteger resolveDepthPlane() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::resolveDepthPlane);
        }

        void setResolveDepthPlane(ns::UInteger resolveDepthPlane) noexcept
        {
            sendMessage(sel::setResolveDepthPlane_, resolveDepthPlane);
        }

        [[nodiscard]] LoadAction loadAction() const noexcept
        {
            return sendMessage<LoadAction>(sel::loadAction);
        }

        void setLoadAction(LoadAction loadAction) noexcept
        {
            sendMessage(sel::setLoadAction_, loadAction);
        }

        [[nodiscard]] StoreAction storeAction() const noexcept
        {
            return sendMessage<StoreAction>(sel::storeAction);
        }

        void setStoreAction(StoreAction storeAction) noexcept
        {
            sendMessage(sel::setStoreAction_, storeAction);
        }

        [[nodiscard]] StoreActionOptions storeActionOptions() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<StoreActionOptions>(sel::storeActionOptions);
        }

        void setStoreActionOptions(StoreActionOptions storeActionOptions) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(sel::setStoreActionOptions_, storeActionOptions);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassColorAttachmentDescriptor final: public RenderPassAttachmentDescriptor
    {
    public:
        [[nodiscard]] ClearColor clearColor() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<ClearColor>(sel::clearColor);
        }

        void setClearColor(ClearColor clearColor) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(sel::setClearColor_, clearColor);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class MultisampleDepthResolveFilter: ns::UInteger
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
            return sendMessage<double>(sel::clearDepth);
        }

        void setClearDepth(double clearDepth) noexcept
        {
            sendMessage(sel::setClearDepth_, clearDepth);
        }

        [[nodiscard]] MultisampleDepthResolveFilter depthResolveFilter() const noexcept API_AVAILABLE(macos(10.14), ios(9.0))
        {
            return sendMessage<MultisampleDepthResolveFilter>(sel::depthResolveFilter);
        }

        void setDepthResolveFilter(MultisampleDepthResolveFilter depthResolveFilter) noexcept API_AVAILABLE(macos(10.14), ios(9.0))
        {
            sendMessage(sel::setDepthResolveFilter_, depthResolveFilter);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class MultisampleStencilResolveFilter: ns::UInteger
    {
        Sample0               = 0,
        DepthResolvedSample   = 1,
    } API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5));

    class RenderPassStencilAttachmentDescriptor final: public ns::Object
    {
    public:
        [[nodiscard]] uint32_t clearStencil() const noexcept
        {
            return sendMessage<uint32_t>(sel::clearStencil);
        }

        void setClearStencil(uint32_t clearStencil) noexcept
        {
            sendMessage(sel::setClearStencil_, clearStencil);
        }

        [[nodiscard]] MultisampleStencilResolveFilter stencilResolveFilter() const noexcept API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
        {
            return sendMessage<MultisampleStencilResolveFilter>(sel::stencilResolveFilter);
        }

        void setStencilResolveFilter(MultisampleStencilResolveFilter stencilResolveFilter) noexcept API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
        {
            sendMessage(sel::setStencilResolveFilter_, stencilResolveFilter);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassColorAttachmentDescriptorArray final: public ns::Object
    {
    public:
        [[nodiscard]] RenderPassColorAttachmentDescriptor operator[](const ns::UInteger index) const noexcept
        {
            return objectAtIndexedSubscript(index);
        }

        [[nodiscard]] RenderPassColorAttachmentDescriptor objectAtIndexedSubscript(const ns::UInteger index) const noexcept
        {
            return getRetained<RenderPassColorAttachmentDescriptor>(ns::sel::objectAtIndexedSubscript_, index);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassDescriptor final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLRenderPassDescriptor");
    public:
        RenderPassDescriptor() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] RenderPassColorAttachmentDescriptorArray colorAttachments() const noexcept
        {
            return getRetained<RenderPassColorAttachmentDescriptorArray>(sel::colorAttachments);
        }

        [[nodiscard]] RenderPassDepthAttachmentDescriptor depthAttachment() const noexcept
        {
            return getRetained<RenderPassDepthAttachmentDescriptor>(sel::depthAttachment);
        }

        [[nodiscard]] RenderPassStencilAttachmentDescriptor stencilAttachment() const noexcept
        {
            return getRetained<RenderPassStencilAttachmentDescriptor>(sel::stencilAttachment);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
