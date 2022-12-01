#ifndef METALPP_METAL_SAMPLER_HPP
#define METALPP_METAL_SAMPLER_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "DepthStencil.hpp"
#include "Selectors.hpp"

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
        static inline const auto cls = objc_lookUpClass("MTLSamplerDescriptor");

        SamplerDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] auto minFilter() const noexcept
        {
            return sendMessage<SamplerMinMagFilter>(sel::minFilter);
        }

        void setMinFilter(const SamplerMinMagFilter minFilter) noexcept
        {
            sendMessage(sel::setMinFilter_, minFilter);
        }

        [[nodiscard]] auto magFilter() const noexcept
        {
            return sendMessage<SamplerMinMagFilter>(sel::magFilter);
        }

        void setMagFilter(const SamplerMinMagFilter magFilter) noexcept
        {
            sendMessage(sel::setMagFilter_, magFilter);
        }

        [[nodiscard]] auto mipFilter() const noexcept
        {
            return sendMessage<SamplerMipFilter>(sel::mipFilter);
        }

        void setMipFilter(const SamplerMipFilter mipFilter) noexcept
        {
            sendMessage(sel::setMipFilter_, mipFilter);
        }

        [[nodiscard]] auto maxAnisotropy() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::maxAnisotropy);
        }

        void setMaxAnisotropy(const ns::UInteger maxAnisotropy) noexcept
        {
            sendMessage(sel::setMaxAnisotropy_, maxAnisotropy);
        }

        [[nodiscard]] auto sAddressMode() const noexcept
        {
            return sendMessage<SamplerAddressMode>(sel::sAddressMode);
        }

        void setSAddressMode(const SamplerAddressMode sAddressMode) noexcept
        {
            sendMessage(sel::setSAddressMode_, sAddressMode);
        }

        [[nodiscard]] auto tAddressMode() const noexcept
        {
            return sendMessage<SamplerAddressMode>(sel::tAddressMode);
        }

        void setTAddressMode(const SamplerAddressMode tAddressMode) noexcept
        {
            sendMessage(sel::setTAddressMode_, tAddressMode);
        }

        [[nodiscard]] auto rAddressMode() const noexcept
        {
            return sendMessage<SamplerAddressMode>(sel::rAddressMode);
        }

        void setRAddressMode(const SamplerAddressMode rAddressMode) noexcept
        {
            sendMessage(sel::setRAddressMode_, rAddressMode);
        }

        [[nodiscard]] auto borderColor() const noexcept
        {
            return sendMessage<SamplerBorderColor>(sel::borderColor);
        }

        void setBorderColor(const SamplerBorderColor borderColor) noexcept
        {
            sendMessage(sel::setBorderColor_, borderColor);
        }

        [[nodiscard]] auto normalizedCoordinates() const noexcept
        {
            return sendMessage<BOOL>(sel::normalizedCoordinates) == YES;
        }

        void setNormalizedCoordinates(const bool normalizedCoordinates) noexcept
        {
            sendMessage(sel::setNormalizedCoordinates_, normalizedCoordinates ? YES : NO);
        }

        [[nodiscard]] auto lodMinClamp() const noexcept
        {
            return sendMessage<float>(sel::lodMinClamp);
        }

        void setLodMinClamp(const float lodMinClamp) noexcept
        {
            sendMessage(sel::setLodMinClamp_, lodMinClamp);
        }

        [[nodiscard]] auto lodMaxClamp() const noexcept
        {
            return sendMessage<float>(sel::lodMaxClamp);
        }

        void setLodMaxClamp(const float lodMaxClamp) noexcept
        {
            sendMessage(sel::setLodMaxClamp_, lodMaxClamp);
        }

        [[nodiscard]] auto lodAverage() const noexcept API_AVAILABLE(ios(9.0), macos(11.0), macCatalyst(14.0))
        {
            return sendMessage<BOOL>(sel::lodAverage) == YES;
        }

        void setLodAverage(const bool lodAverage) noexcept API_AVAILABLE(ios(9.0), macos(11.0), macCatalyst(14.0))
        {
            sendMessage(sel::setLodAverage_, lodAverage ? YES : NO);
        }

        [[nodiscard]] auto compareFunction() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<CompareFunction>(sel::compareFunction);
        }

        void setCompareFunction(const CompareFunction compareFunction) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(sel::setCompareFunction_, compareFunction);
        }

        [[nodiscard]] auto supportArgumentBuffers() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<BOOL>(sel::supportArgumentBuffers) == YES;
        }

        void setSupportArgumentBuffers(const bool supportArgumentBuffers) noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            sendMessage(sel::setSupportArgumentBuffers_, supportArgumentBuffers ? YES : NO);
        }

        [[nodiscard]] auto label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, label.get());
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class SamplerState final: public ns::Object
    {
    public:
        SamplerState() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
