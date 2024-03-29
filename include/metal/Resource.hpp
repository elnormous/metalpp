#ifndef METALPP_METAL_RESOURCE_HPP
#define METALPP_METAL_RESOURCE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class Device;
    class Heap;

    enum class PurgeableState: ns::UInteger
    {
        KeepCurrent = 1,

        NonVolatile = 2,
        Volatile = 3,
        Empty = 4,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class CPUCacheMode: ns::UInteger
    {
        DefaultCache = 0,
        WriteCombined = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StorageMode: ns::UInteger
    {
        Shared  = 0,
        Managed API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios) = 1,
        Private = 2,
        Memoryless API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(10.0)) = 3,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class HazardTrackingMode: ns::UInteger
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

    enum class ResourceOptions: ns::UInteger
    {
        None = 0,

        CPUCacheModeDefaultCache  = static_cast<ns::UInteger>(CPUCacheMode::DefaultCache)  << CPUCacheModeShift,
        CPUCacheModeWriteCombined = static_cast<ns::UInteger>(CPUCacheMode::WriteCombined) << CPUCacheModeShift,

        StorageModeShared API_AVAILABLE(macos(10.11), ios(9.0)) = static_cast<ns::UInteger>(StorageMode::Shared) << StorageModeShift,
        StorageModeManaged API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios) = static_cast<ns::UInteger>(StorageMode::Managed) << StorageModeShift,
        StorageModePrivate API_AVAILABLE(macos(10.11), ios(9.0)) = static_cast<ns::UInteger>(StorageMode::Private) << StorageModeShift,
        StorageModeMemoryless API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(10.0)) = static_cast<ns::UInteger>(StorageMode::Memoryless) << StorageModeShift,

        HazardTrackingModeDefault API_AVAILABLE(macos(10.13), ios(10.0)) = static_cast<ns::UInteger>(HazardTrackingMode::Default) << HazardTrackingModeShift,
        HazardTrackingModeUntracked API_AVAILABLE(macos(10.13), ios(10.0)) = static_cast<ns::UInteger>(HazardTrackingMode::Untracked) << HazardTrackingModeShift,
        HazardTrackingModeTracked API_AVAILABLE(macos(10.15), ios(13.0)) = static_cast<ns::UInteger>(HazardTrackingMode::Tracked) << HazardTrackingModeShift,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    [[nodiscard]] inline constexpr ResourceOptions operator&(const ResourceOptions a, const ResourceOptions b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) & static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    [[nodiscard]] inline constexpr ResourceOptions operator|(const ResourceOptions a, const ResourceOptions b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) | static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    [[nodiscard]] inline constexpr ResourceOptions operator^(const ResourceOptions a, const ResourceOptions b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) ^ static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    [[nodiscard]] inline constexpr ResourceOptions operator~(const ResourceOptions a) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ResourceOptions>(~static_cast<std::underlying_type_t<ResourceOptions>>(a));
    }
    inline constexpr ResourceOptions& operator&=(ResourceOptions& a, const ResourceOptions b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return a = static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) & static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions& operator|=(ResourceOptions& a, const ResourceOptions b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return a = static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) | static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }
    inline constexpr ResourceOptions& operator^=(ResourceOptions& a, const ResourceOptions b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return a = static_cast<ResourceOptions>(static_cast<std::underlying_type_t<ResourceOptions>>(a) ^ static_cast<std::underlying_type_t<ResourceOptions>>(b));
    }

    class Resource: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(cpuCacheMode, "cpuCacheMode");
        METALPP_PRIVATE_SEL(storageMode, "storageMode");
        METALPP_PRIVATE_SEL(hazardTrackingMode, "hazardTrackingMode");
        METALPP_PRIVATE_SEL(resourceOptions, "resourceOptions");
        METALPP_PRIVATE_SEL(setPurgeableState_, "setPurgeableState:");
        METALPP_PRIVATE_SEL(heap, "heap");
        METALPP_PRIVATE_SEL(heapOffset, "heapOffset");
        METALPP_PRIVATE_SEL(allocatedSize, "allocatedSize");
        METALPP_PRIVATE_SEL(makeAliasable, "makeAliasable");
        METALPP_PRIVATE_SEL(isAliasable, "isAliasable");

        using Object::Object;
        using Object::operator=;
        
        Resource() = delete;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto cpuCacheMode() const noexcept
        {
            return sendMessage<CPUCacheMode>(METALPP_SEL(cpuCacheMode));
        }

        [[nodiscard]] auto storageMode() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<StorageMode>(METALPP_SEL(storageMode));
        }

        [[nodiscard]] auto hazardTrackingMode() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HazardTrackingMode>(METALPP_SEL(hazardTrackingMode));
        }

        [[nodiscard]] auto resourceOptions() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<ResourceOptions>(METALPP_SEL(resourceOptions));
        }

        [[nodiscard]] auto setPurgeableState(const PurgeableState state) noexcept
        {
            return sendMessage<PurgeableState>(METALPP_SEL(setPurgeableState_), state);
        }

        [[nodiscard]] Heap heap() const noexcept API_AVAILABLE(macos(10.13), ios(10.0));

        [[nodiscard]] auto heapOffset() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(heapOffset));
        }

        [[nodiscard]] auto allocatedSize() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(allocatedSize));
        }

        void makeAliasable() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(makeAliasable));
        }

        [[nodiscard]] auto isAliasable() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(isAliasable)) == YES;
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
