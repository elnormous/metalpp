#ifndef METALPP_METAL_SAMPLER_HPP
#define METALPP_METAL_SAMPLER_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "DepthStencil.hpp"

namespace mtl
{
    class Device;

    enum class SamplerMinMagFilter: ns::UInteger
    {
        Nearest = 0,
        Linear = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class SamplerMipFilter: ns::UInteger
    {
        NotMipmapped = 0,
        Nearest = 1,
        Linear = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class SamplerBorderColor: ns::UInteger
    {
        TransparentBlack = 0,  // {0,0,0,0}
        OpaqueBlack = 1,       // {0,0,0,1}
        OpaqueWhite = 2,       // {1,1,1,1}
    } API_AVAILABLE(macos(10.12), ios(14.0));

    enum class SamplerAddressMode: ns::UInteger
    {
        ClampToEdge = 0,
        MirrorClampToEdge API_AVAILABLE(macos(10.11), ios(14.0)) = 1,
        Repeat = 2,
        MirrorRepeat = 3,
        ClampToZero = 4,
        ClampToBorderColor API_AVAILABLE(macos(10.12), ios(14.0)) = 5,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class SamplerDescriptor final: public ns::Object
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLSamplerDescriptor");

        METALPP_PRIVATE_SEL(minFilter, "minFilter");
        METALPP_PRIVATE_SEL(setMinFilter_, "setMinFilter:");
        METALPP_PRIVATE_SEL(magFilter, "magFilter");
        METALPP_PRIVATE_SEL(setMagFilter_, "setMagFilter:");
        METALPP_PRIVATE_SEL(mipFilter, "mipFilter");
        METALPP_PRIVATE_SEL(setMipFilter_, "setMipFilter:");
        METALPP_PRIVATE_SEL(maxAnisotropy, "maxAnisotropy");
        METALPP_PRIVATE_SEL(setMaxAnisotropy_, "setMaxAnisotropy:");
        METALPP_PRIVATE_SEL(sAddressMode, "sAddressMode");
        METALPP_PRIVATE_SEL(setSAddressMode_, "setSAddressMode:");
        METALPP_PRIVATE_SEL(tAddressMode, "tAddressMode");
        METALPP_PRIVATE_SEL(setTAddressMode_, "setTAddressMode:");
        METALPP_PRIVATE_SEL(rAddressMode, "rAddressMode");
        METALPP_PRIVATE_SEL(setRAddressMode_, "setRAddressMode:");
        METALPP_PRIVATE_SEL(borderColor, "borderColor");
        METALPP_PRIVATE_SEL(setBorderColor_, "setBorderColor:");
        METALPP_PRIVATE_SEL(normalizedCoordinates, "normalizedCoordinates");
        METALPP_PRIVATE_SEL(setNormalizedCoordinates_, "setNormalizedCoordinates:");
        METALPP_PRIVATE_SEL(lodMinClamp, "lodMinClamp");
        METALPP_PRIVATE_SEL(setLodMinClamp_, "setLodMinClamp:");
        METALPP_PRIVATE_SEL(lodMaxClamp, "lodMaxClamp");
        METALPP_PRIVATE_SEL(setLodMaxClamp_, "setLodMaxClamp:");
        METALPP_PRIVATE_SEL(lodAverage, "lodAverage");
        METALPP_PRIVATE_SEL(setLodAverage_, "setLodAverage:");
        METALPP_PRIVATE_SEL(compareFunction, "compareFunction");
        METALPP_PRIVATE_SEL(setCompareFunction_, "setCompareFunction:");
        METALPP_PRIVATE_SEL(supportArgumentBuffers, "supportArgumentBuffers");
        METALPP_PRIVATE_SEL(setSupportArgumentBuffers_, "setSupportArgumentBuffers:");
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");

        SamplerDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto minFilter() const noexcept
        {
            return sendMessage<SamplerMinMagFilter>(METALPP_SEL(minFilter));
        }

        void setMinFilter(const SamplerMinMagFilter minFilter) noexcept
        {
            sendMessage(METALPP_SEL(setMinFilter_), minFilter);
        }

        [[nodiscard]] auto magFilter() const noexcept
        {
            return sendMessage<SamplerMinMagFilter>(METALPP_SEL(magFilter));
        }

        void setMagFilter(const SamplerMinMagFilter magFilter) noexcept
        {
            sendMessage(METALPP_SEL(setMagFilter_), magFilter);
        }

        [[nodiscard]] auto mipFilter() const noexcept
        {
            return sendMessage<SamplerMipFilter>(METALPP_SEL(mipFilter));
        }

        void setMipFilter(const SamplerMipFilter mipFilter) noexcept
        {
            sendMessage(METALPP_SEL(setMipFilter_), mipFilter);
        }

        [[nodiscard]] auto maxAnisotropy() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxAnisotropy));
        }

        void setMaxAnisotropy(const ns::UInteger maxAnisotropy) noexcept
        {
            sendMessage(METALPP_SEL(setMaxAnisotropy_), maxAnisotropy);
        }

        [[nodiscard]] auto sAddressMode() const noexcept
        {
            return sendMessage<SamplerAddressMode>(METALPP_SEL(sAddressMode));
        }

        void setSAddressMode(const SamplerAddressMode sAddressMode) noexcept
        {
            sendMessage(METALPP_SEL(setSAddressMode_), sAddressMode);
        }

        [[nodiscard]] auto tAddressMode() const noexcept
        {
            return sendMessage<SamplerAddressMode>(METALPP_SEL(tAddressMode));
        }

        void setTAddressMode(const SamplerAddressMode tAddressMode) noexcept
        {
            sendMessage(METALPP_SEL(setTAddressMode_), tAddressMode);
        }

        [[nodiscard]] auto rAddressMode() const noexcept
        {
            return sendMessage<SamplerAddressMode>(METALPP_SEL(rAddressMode));
        }

        void setRAddressMode(const SamplerAddressMode rAddressMode) noexcept
        {
            sendMessage(METALPP_SEL(setRAddressMode_), rAddressMode);
        }

        [[nodiscard]] auto borderColor() const noexcept
        {
            return sendMessage<SamplerBorderColor>(METALPP_SEL(borderColor));
        }

        void setBorderColor(const SamplerBorderColor borderColor) noexcept
        {
            sendMessage(METALPP_SEL(setBorderColor_), borderColor);
        }

        [[nodiscard]] auto normalizedCoordinates() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(normalizedCoordinates)) == YES;
        }

        void setNormalizedCoordinates(const bool normalizedCoordinates) noexcept
        {
            sendMessage(METALPP_SEL(setNormalizedCoordinates_), normalizedCoordinates ? YES : NO);
        }

        [[nodiscard]] auto lodMinClamp() const noexcept
        {
            return sendMessage<float>(METALPP_SEL(lodMinClamp));
        }

        void setLodMinClamp(const float lodMinClamp) noexcept
        {
            sendMessage(METALPP_SEL(setLodMinClamp_), lodMinClamp);
        }

        [[nodiscard]] auto lodMaxClamp() const noexcept
        {
            return sendMessage<float>(METALPP_SEL(lodMaxClamp));
        }

        void setLodMaxClamp(const float lodMaxClamp) noexcept
        {
            sendMessage(METALPP_SEL(setLodMaxClamp_), lodMaxClamp);
        }

        [[nodiscard]] auto lodAverage() const noexcept API_AVAILABLE(ios(9.0), macos(11.0), macCatalyst(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(lodAverage)) == YES;
        }

        void setLodAverage(const bool lodAverage) noexcept API_AVAILABLE(ios(9.0), macos(11.0), macCatalyst(14.0))
        {
            sendMessage(METALPP_SEL(setLodAverage_), lodAverage ? YES : NO);
        }

        [[nodiscard]] auto compareFunction() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<CompareFunction>(METALPP_SEL(compareFunction));
        }

        void setCompareFunction(const CompareFunction compareFunction) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(METALPP_SEL(setCompareFunction_), compareFunction);
        }

        [[nodiscard]] auto supportArgumentBuffers() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportArgumentBuffers)) == YES;
        }

        void setSupportArgumentBuffers(const bool supportArgumentBuffers) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(METALPP_SEL(setSupportArgumentBuffers_), supportArgumentBuffers ? YES : NO);
        }

        [[nodiscard]] auto label() const noexcept
        {
            return getRetained<ns::String>(METALPP_SEL(label));
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class SamplerState final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(label, "label");

        using Object::Object;

        SamplerState() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto label() const noexcept
        {
            return getRetained<ns::String>(METALPP_SEL(label));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
