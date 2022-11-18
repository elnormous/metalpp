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

    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
