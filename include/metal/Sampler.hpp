#ifndef METALPP_METAL_SAMPLER_HPP
#define METALPP_METAL_SAMPLER_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"

namespace mtl
{
    enum class SamplerMinMagFilter: NSUInteger
    {
        Nearest = 0,
        Linear = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class SamplerMipFilter: NSUInteger
    {
        NotMipmapped = 0,
        Nearest = 1,
        Linear = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class SamplerBorderColor: NSUInteger
    {
        TransparentBlack = 0,  // {0,0,0,0}
        OpaqueBlack = 1,       // {0,0,0,1}
        OpaqueWhite = 2,       // {1,1,1,1}
    } API_AVAILABLE(macos(10.12), ios(14.0));

    enum class SamplerAddressMode: NSUInteger
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
        static inline const auto cls = objc_lookUpClass("MTLSamplerDescriptor");
    public:
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
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class SamplerState final: public ns::Object
    {
    public:
        SamplerState() = delete;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
