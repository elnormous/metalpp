#ifndef METALPP_METAL_RENDERPASS_HPP
#define METALPP_METAL_RENDERPASS_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "Texture.hpp"

namespace mtl
{
    struct ClearColor final
    {
        ClearColor() noexcept = default;
        ClearColor(double r, double g, double b, double a) noexcept: red{r}, green{g}, blue{b}, alpha{a} {}

        [[nodiscard]] bool operator==(const ClearColor& other) const noexcept
        {
            return other.red == red && other.green == green && other.blue == blue && other.alpha == alpha;
        }

        [[nodiscard]] bool operator!=(const ClearColor& other) const noexcept
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
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLRenderPassAttachmentDescriptor");

        METALPP_PRIVATE_SEL(texture, "texture");
        METALPP_PRIVATE_SEL(setTexture_, "setTexture:");
        METALPP_PRIVATE_SEL(level, "level");
        METALPP_PRIVATE_SEL(setLevel_, "setLevel:");
        METALPP_PRIVATE_SEL(slice, "slice");
        METALPP_PRIVATE_SEL(setSlice_, "setSlice:");
        METALPP_PRIVATE_SEL(depthPlane, "depthPlane");
        METALPP_PRIVATE_SEL(setDepthPlane_, "setDepthPlane:");
        METALPP_PRIVATE_SEL(resolveTexture, "resolveTexture");
        METALPP_PRIVATE_SEL(setResolveTexture_, "setResolveTexture:");
        METALPP_PRIVATE_SEL(resolveLevel, "resolveLevel");
        METALPP_PRIVATE_SEL(setResolveLevel_, "setResolveLevel:");
        METALPP_PRIVATE_SEL(resolveSlice, "resolveSlice");
        METALPP_PRIVATE_SEL(setResolveSlice_, "setResolveSlice:");
        METALPP_PRIVATE_SEL(resolveDepthPlane, "resolveDepthPlane");
        METALPP_PRIVATE_SEL(setResolveDepthPlane_, "setResolveDepthPlane:");
        METALPP_PRIVATE_SEL(loadAction, "loadAction");
        METALPP_PRIVATE_SEL(setLoadAction_, "setLoadAction:");
        METALPP_PRIVATE_SEL(storeAction, "storeAction");
        METALPP_PRIVATE_SEL(setStoreAction_, "setStoreAction:");
        METALPP_PRIVATE_SEL(storeActionOptions, "storeActionOptions");
        METALPP_PRIVATE_SEL(setStoreActionOptions_, "setStoreActionOptions:");
        METALPP_PRIVATE_SEL(clearColor, "clearColor");
        METALPP_PRIVATE_SEL(setClearColor_, "setClearColor:");

        using Object::Object;

        RenderPassAttachmentDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto texture() const noexcept
        {
            return Texture{sendMessage<id>(METALPP_SEL(texture))};
        }

        void setTexture(const Texture& texture) noexcept
        {
            sendMessage(METALPP_SEL(setTexture_), texture.get());
        }

        [[nodiscard]] auto level() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(level));
        }

        void setLevel(ns::UInteger level) noexcept
        {
            sendMessage(METALPP_SEL(setLevel_), level);
        }

        [[nodiscard]] auto slice() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(slice));
        }

        void setSlice(ns::UInteger slice) noexcept
        {
            sendMessage(METALPP_SEL(setSlice_), slice);
        }

        [[nodiscard]] auto depthPlane() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(depthPlane));
        }

        void setDepthPlane(ns::UInteger depthPlane) noexcept
        {
            sendMessage(METALPP_SEL(setDepthPlane_), depthPlane);
        }

        [[nodiscard]] auto resolveTexture() const noexcept
        {
            return Texture{sendMessage<id>(METALPP_SEL(resolveTexture))};
        }

        void setResolveTexture(const Texture& resolveTexture) noexcept
        {
            sendMessage(METALPP_SEL(setResolveTexture_), resolveTexture.get());
        }

        [[nodiscard]] auto resolveLevel() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(resolveLevel));
        }

        void setResolveLevel(ns::UInteger resolveLevel) noexcept
        {
            sendMessage(METALPP_SEL(setResolveLevel_), resolveLevel);
        }

        [[nodiscard]] auto resolveSlice() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(resolveSlice));
        }

        void setResolveSlice(ns::UInteger resolveSlice) noexcept
        {
            sendMessage(METALPP_SEL(setResolveSlice_), resolveSlice);
        }

        [[nodiscard]] auto resolveDepthPlane() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(resolveDepthPlane));
        }

        void setResolveDepthPlane(ns::UInteger resolveDepthPlane) noexcept
        {
            sendMessage(METALPP_SEL(setResolveDepthPlane_), resolveDepthPlane);
        }

        [[nodiscard]] auto loadAction() const noexcept
        {
            return sendMessage<LoadAction>(METALPP_SEL(loadAction));
        }

        void setLoadAction(LoadAction loadAction) noexcept
        {
            sendMessage(METALPP_SEL(setLoadAction_), loadAction);
        }

        [[nodiscard]] auto storeAction() const noexcept
        {
            return sendMessage<StoreAction>(METALPP_SEL(storeAction));
        }

        void setStoreAction(StoreAction storeAction) noexcept
        {
            sendMessage(METALPP_SEL(setStoreAction_), storeAction);
        }

        [[nodiscard]] auto storeActionOptions() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<StoreActionOptions>(METALPP_SEL(storeActionOptions));
        }

        void setStoreActionOptions(StoreActionOptions storeActionOptions) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(setStoreActionOptions_), storeActionOptions);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassColorAttachmentDescriptor final: public RenderPassAttachmentDescriptor
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLRenderPassColorAttachmentDescriptor");

        using RenderPassAttachmentDescriptor::RenderPassAttachmentDescriptor;

        RenderPassColorAttachmentDescriptor() noexcept:
            RenderPassAttachmentDescriptor{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto clearColor() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<ClearColor>(METALPP_SEL(clearColor));
        }

        void setClearColor(ClearColor clearColor) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(setClearColor_), clearColor);
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
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLRenderPassDepthAttachmentDescriptor");

        METALPP_PRIVATE_SEL(clearDepth, "clearDepth");
        METALPP_PRIVATE_SEL(setClearDepth_, "setClearDepth:");
        METALPP_PRIVATE_SEL(depthResolveFilter, "depthResolveFilter");
        METALPP_PRIVATE_SEL(setDepthResolveFilter_, "setDepthResolveFilter:");

        using Object::Object;

        RenderPassDepthAttachmentDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto clearDepth() const noexcept
        {
            return sendMessage<double>(METALPP_SEL(clearDepth));
        }

        void setClearDepth(double clearDepth) noexcept
        {
            sendMessage(METALPP_SEL(setClearDepth_), clearDepth);
        }

        [[nodiscard]] auto depthResolveFilter() const noexcept API_AVAILABLE(macos(10.14), ios(9.0))
        {
            return sendMessage<MultisampleDepthResolveFilter>(METALPP_SEL(depthResolveFilter));
        }

        void setDepthResolveFilter(MultisampleDepthResolveFilter depthResolveFilter) noexcept API_AVAILABLE(macos(10.14), ios(9.0))
        {
            sendMessage(METALPP_SEL(setDepthResolveFilter_), depthResolveFilter);
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
        METALPP_PRIVATE_CLS("MTLRenderPassStencilAttachmentDescriptor");

        METALPP_PRIVATE_SEL(clearStencil, "clearStencil");
        METALPP_PRIVATE_SEL(setClearStencil_, "setClearStencil:");
        METALPP_PRIVATE_SEL(stencilResolveFilter, "stencilResolveFilter");
        METALPP_PRIVATE_SEL(setStencilResolveFilter_, "setStencilResolveFilter:");

        using Object::Object;

        RenderPassStencilAttachmentDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto clearStencil() const noexcept
        {
            return sendMessage<uint32_t>(METALPP_SEL(clearStencil));
        }

        void setClearStencil(uint32_t clearStencil) noexcept
        {
            sendMessage(METALPP_SEL(setClearStencil_), clearStencil);
        }

        [[nodiscard]] auto stencilResolveFilter() const noexcept API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
        {
            return sendMessage<MultisampleStencilResolveFilter>(METALPP_SEL(stencilResolveFilter));
        }

        void setStencilResolveFilter(MultisampleStencilResolveFilter stencilResolveFilter) noexcept API_AVAILABLE(macos(10.14), ios(12.0), tvos(14.5))
        {
            sendMessage(METALPP_SEL(setStencilResolveFilter_), stencilResolveFilter);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassColorAttachmentDescriptorArray final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(objectAtIndexedSubscript_, "objectAtIndexedSubscript:");
        METALPP_PRIVATE_SEL(setObject_atIndexedSubscript_, "setObject:atIndexedSubscript:");

        using Object::Object;
        
        [[nodiscard]] auto object(const ns::UInteger index) const noexcept
        {
            return RenderPassColorAttachmentDescriptor{sendMessage<id>(METALPP_SEL(objectAtIndexedSubscript_), index)};
        }

        void setObject(const RenderPassColorAttachmentDescriptor& derscriptor) noexcept
        {
            sendMessage(METALPP_SEL(setObject_atIndexedSubscript_), derscriptor, index);
        }

        [[nodiscard]] auto operator[](const ns::UInteger index) const noexcept
        {
            return object(index);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPassDescriptor final: public ns::Object
    {
    public:
        METALPP_PRIVATE_CLS("MTLRenderPassDescriptor");

        METALPP_PRIVATE_SEL(colorAttachments, "colorAttachments");
        METALPP_PRIVATE_SEL(depthAttachment, "depthAttachment");
        METALPP_PRIVATE_SEL(stencilAttachment, "stencilAttachment");

        RenderPassDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto colorAttachments() const noexcept
        {
            return RenderPassColorAttachmentDescriptorArray{sendMessage<id>(METALPP_SEL(colorAttachments))};
        }

        [[nodiscard]] auto depthAttachment() const noexcept
        {
            return RenderPassDepthAttachmentDescriptor{sendMessage<id>(METALPP_SEL(depthAttachment))};
        }

        [[nodiscard]] auto stencilAttachment() const noexcept
        {
            return RenderPassStencilAttachmentDescriptor{sendMessage<id>(METALPP_SEL(stencilAttachment))};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
