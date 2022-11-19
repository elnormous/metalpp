#ifndef METALPP_METAL_RESOURCE_HPP
#define METALPP_METAL_RESOURCE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../foundation/String.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    enum class CPUCacheMode: NSUInteger
    {
        DefaultCache = 0,
        WriteCombined = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StorageMode: NSUInteger
    {
        Shared  = 0,
        Managed API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios) = 1,
        Private = 2,
        Memoryless API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(10.0)) = 3,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class HazardTrackingMode: NSUInteger
    {
        Default = 0,
        Untracked = 1,
        Tracked = 2,
    } API_AVAILABLE(macos(10.15), ios(13.0));

    constexpr auto CPUCacheModeShift =       0;
    constexpr auto CPUCacheModeMask =        0xfUL << CPUCacheModeShift;

    constexpr auto StorageModeShift =        4;
    constexpr auto StorageModeMask =         0xfUL << StorageModeShift;

    constexpr auto HazardTrackingModeShift = 8;
    constexpr auto HazardTrackingModeMask =  0x3UL << HazardTrackingModeShift;

    enum class ResourceOptions: NSUInteger
    {
        CPUCacheModeDefaultCache  = static_cast<NSUInteger>(CPUCacheMode::DefaultCache)  << CPUCacheModeShift,
        CPUCacheModeWriteCombined = static_cast<NSUInteger>(CPUCacheMode::WriteCombined) << CPUCacheModeShift,

        StorageModeShared API_AVAILABLE(macos(10.11), ios(9.0)) = static_cast<NSUInteger>(StorageMode::Shared) << StorageModeShift,
        StorageModeManaged API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios) = static_cast<NSUInteger>(StorageMode::Managed) << StorageModeShift,
        StorageModePrivate API_AVAILABLE(macos(10.11), ios(9.0)) = static_cast<NSUInteger>(StorageMode::Private) << StorageModeShift,
        StorageModeMemoryless API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(10.0)) = static_cast<NSUInteger>(StorageMode::Memoryless) << StorageModeShift,

        HazardTrackingModeDefault API_AVAILABLE(macos(10.13), ios(10.0)) = static_cast<NSUInteger>(HazardTrackingMode::Default) << HazardTrackingModeShift,
        HazardTrackingModeUntracked API_AVAILABLE(macos(10.13), ios(10.0)) = static_cast<NSUInteger>(HazardTrackingMode::Untracked) << HazardTrackingModeShift,
        HazardTrackingModeTracked API_AVAILABLE(macos(10.15), ios(13.0)) = static_cast<NSUInteger>(HazardTrackingMode::Tracked) << HazardTrackingModeShift,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    inline constexpr ResourceOptions operator&(const ResourceOptions a, const ResourceOptions b) noexcept
    {
        return static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) & static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions operator|(const ResourceOptions a, const ResourceOptions b) noexcept
    {
        return static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) | static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions operator^(const ResourceOptions a, const ResourceOptions b) noexcept
    {
        return static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) ^ static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions operator~(const ResourceOptions a) noexcept
    {
        return static_cast<ResourceOptions>(~static_cast<std::underlying_type_t<ResourceOptions>>(a));
    }
    inline constexpr ResourceOptions& operator&=(ResourceOptions& a, const ResourceOptions b) noexcept
    {
        return a = static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) & static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions& operator|=(ResourceOptions& a, const ResourceOptions b) noexcept
    {
        return a = static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) | static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions& operator^=(ResourceOptions& a, const ResourceOptions b) noexcept
    {
        return a = static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) ^ static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }

    class Resource: public ns::Object
    {
    public:
        Resource() = delete;

        Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String& label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] CPUCacheMode cpuCacheMode() const noexcept
        {
            return objc::sendMessage<CPUCacheMode>(*this, sel::cpuCacheMode);
        }

        [[nodiscard]] StorageMode storageMode() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return objc::sendMessage<StorageMode>(*this, sel::storageMode);
        }

        [[nodiscard]] HazardTrackingMode hazardTrackingMode() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return objc::sendMessage<HazardTrackingMode>(*this, sel::hazardTrackingMode);
        }

        [[nodiscard]] ResourceOptions resourceOptions() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return objc::sendMessage<ResourceOptions>(*this, sel::resourceOptions);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
