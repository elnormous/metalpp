#ifndef METALPP_METAL_HEAP_HPP
#define METALPP_METAL_HEAP_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Object.hpp"
#include "Buffer.hpp"
#include "Resource.hpp"
#include "Texture.hpp"

namespace mtl
{
    class Device;
    enum class SparsePageSize: ns::Integer;

    enum class HeapType: NSInteger
    {
        Automatic = 0,
        Placement = 1,
        Sparse API_AVAILABLE(macos(11.0), macCatalyst(14.0)) = 2,
    } API_AVAILABLE(macos(10.15), ios(13.0));

    class HeapDescriptor final: public ns::Object, public ns::Copying
    {
    public:
        METALPP_PRIVATE_CLS("MTLHeapDescriptor");

        METALPP_PRIVATE_SEL(size, "size");
        METALPP_PRIVATE_SEL(setSize_, "setSize:");
        METALPP_PRIVATE_SEL(storageMode, "storageMode");
        METALPP_PRIVATE_SEL(setStorageMode_, "setStorageMode:");
        METALPP_PRIVATE_SEL(cpuCacheMode, "cpuCacheMode");
        METALPP_PRIVATE_SEL(setCpuCacheMode_, "setCpuCacheMode:");
        METALPP_PRIVATE_SEL(sparsePageSize, "sparsePageSize");
        METALPP_PRIVATE_SEL(setSparsePageSize_, "setSparsePageSize:");
        METALPP_PRIVATE_SEL(hazardTrackingMode, "hazardTrackingMode");
        METALPP_PRIVATE_SEL(setHazardTrackingMode_, "setHazardTrackingMode:");
        METALPP_PRIVATE_SEL(resourceOptions, "resourceOptions");
        METALPP_PRIVATE_SEL(setResourceOptions_, "setResourceOptions:");
        METALPP_PRIVATE_SEL(type, "type");
        METALPP_PRIVATE_SEL(setType_, "setType:");

        HeapDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto size() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(size));
        }

        void setSize(const ns::UInteger size) noexcept
        {
            sendMessage(METALPP_SEL(setSize_), size);
        }

        [[nodiscard]] auto storageMode() const noexcept
        {
            return sendMessage<StorageMode>(METALPP_SEL(storageMode));
        }

        void setStorageMode(const StorageMode storageMode) noexcept
        {
            sendMessage(METALPP_SEL(setStorageMode_), storageMode);
        }

        [[nodiscard]] auto cpuCacheMode() const noexcept
        {
            return sendMessage<CPUCacheMode>(METALPP_SEL(cpuCacheMode));
        }

        void setCpuCacheMode(const CPUCacheMode cpuCacheMode) noexcept
        {
            sendMessage(METALPP_SEL(setCpuCacheMode_), cpuCacheMode);
        }

        [[nodiscard]] auto sparsePageSize() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<SparsePageSize>(METALPP_SEL(sparsePageSize));
        }

        void setSparsePageSize(const SparsePageSize sparsePageSize) noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            sendMessage(METALPP_SEL(setSparsePageSize_), sparsePageSize);
        }

        [[nodiscard]] auto hazardTrackingMode() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HazardTrackingMode>(METALPP_SEL(hazardTrackingMode));
        }

        void setHazardTrackingMode(const HazardTrackingMode hazardTrackingMode) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(setHazardTrackingMode_), hazardTrackingMode);
        }

        [[nodiscard]] auto resourceOptions() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<ResourceOptions>(METALPP_SEL(resourceOptions));
        }

        void setResourceOptions(const ResourceOptions resourceOptions) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(setResourceOptions_), resourceOptions);
        }

        [[nodiscard]] auto type() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HeapType>(METALPP_SEL(type));
        }

        void setType(const HeapType type) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(setType_), type);
        }
    } API_AVAILABLE(macos(10.13), ios(10.0));

    class Heap final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(storageMode, "storageMode");
        METALPP_PRIVATE_SEL(cpuCacheMode, "cpuCacheMode");
        METALPP_PRIVATE_SEL(hazardTrackingMode, "hazardTrackingMode");
        METALPP_PRIVATE_SEL(resourceOptions, "resourceOptions");
        METALPP_PRIVATE_SEL(size, "size");
        METALPP_PRIVATE_SEL(usedSize, "usedSize");
        METALPP_PRIVATE_SEL(currentAllocatedSize, "currentAllocatedSize");
        METALPP_PRIVATE_SEL(maxAvailableSizeWithAlignment_, "maxAvailableSizeWithAlignment:");
        METALPP_PRIVATE_SEL(newBufferWithLength_options_, "newBufferWithLength:options:");
        METALPP_PRIVATE_SEL(newTextureWithDescriptor_, "newTextureWithDescriptor:");
        METALPP_PRIVATE_SEL(setPurgeableState_, "setPurgeableState:");
        METALPP_PRIVATE_SEL(type, "type");
        METALPP_PRIVATE_SEL(newBufferWithLength_options_offset_, "newBufferWithLength:options:offset:");
        METALPP_PRIVATE_SEL(newTextureWithDescriptor_offset_, "newTextureWithDescriptor:offset:");
        
        using Object::Object;
        using Object::operator=;

        Heap() = delete;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto storageMode() const noexcept
        {
            return sendMessage<StorageMode>(METALPP_SEL(storageMode));
        }

        [[nodiscard]] auto cpuCacheMode() const noexcept
        {
            return sendMessage<CPUCacheMode>(METALPP_SEL(cpuCacheMode));
        }

        [[nodiscard]] auto hazardTrackingMode() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HazardTrackingMode>(METALPP_SEL(hazardTrackingMode));
        }

        [[nodiscard]] auto resourceOptions() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<ResourceOptions>(METALPP_SEL(resourceOptions));
        }

        [[nodiscard]] auto size() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(size));
        }

        [[nodiscard]] auto usedSize() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(usedSize));
        }

        [[nodiscard]] auto currentAllocatedSize() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(currentAllocatedSize));
        }

        [[nodiscard]] auto maxAvailableSize(const ns::UInteger alignment) const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxAvailableSizeWithAlignment_), alignment);
        }

        [[nodiscard]] auto newBuffer(const ns::UInteger length,
                                     const ResourceOptions options) const noexcept
        {
            id buffer = sendMessage<id>(METALPP_SEL(newBufferWithLength_options_),
                                        length,
                                        options);
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newTexture(const TextureDescriptor& desc) const noexcept
        {
            id texture = sendMessage<id>(METALPP_SEL(newTextureWithDescriptor_), desc.get());
            return Texture{texture, ns::adopt};
        }

        [[nodiscard]] auto setPurgeableState(const PurgeableState state) noexcept
        {
            return sendMessage<PurgeableState>(METALPP_SEL(setPurgeableState_), state);
        }

        [[nodiscard]] auto type() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HeapType>(METALPP_SEL(type));
        }

        [[nodiscard]] auto newBuffer(const ns::UInteger length,
                                     const ResourceOptions options,
                                     const ns::UInteger offset) const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            id buffer = sendMessage<id>(METALPP_SEL(newBufferWithLength_options_offset_),
                                        length,
                                        options,
                                        offset);
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newTexture(const TextureDescriptor descriptor,
                                      const ns::UInteger offset) const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            id texture = sendMessage<id>(METALPP_SEL(newTextureWithDescriptor_offset_),
                                         descriptor,
                                         offset);
            return Texture{texture, ns::adopt};
        }
    } API_AVAILABLE(macos(10.13), ios(10.0));

    [[nodiscard]] inline Heap Resource::heap() const noexcept API_AVAILABLE(macos(10.13), ios(10.0))
    {
        return Heap{sendMessage<id>(METALPP_SEL(heap))};
    }
}

#endif
