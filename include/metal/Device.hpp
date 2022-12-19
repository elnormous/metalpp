#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <dlfcn.h>
#include <type_traits>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/Error.hpp"
#include "../foundation/String.hpp"
#include "Buffer.hpp"
#include "CommandBuffer.hpp"
#include "CommandEncoder.hpp"
#include "CommandQueue.hpp"
#include "DepthStencil.hpp"
#include "DynamicLibrary.hpp"
#include "Library.hpp"
#include "RenderPipeline.hpp"
#include "Resource.hpp"
#include "Sampler.hpp"
#include "Texture.hpp"

enum class FeatureSet: ns::UInteger
{
    iOS_GPUFamily1_v1 API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 0,
    iOS_GPUFamily2_v1 API_AVAILABLE(ios(8.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 1,

    iOS_GPUFamily1_v2 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 2,
    iOS_GPUFamily2_v2 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 3,
    iOS_GPUFamily3_v1 API_AVAILABLE(ios(9.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 4,

    iOS_GPUFamily1_v3 API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 5,
    iOS_GPUFamily2_v3 API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 6,
    iOS_GPUFamily3_v2 API_AVAILABLE(ios(10.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 7,

    iOS_GPUFamily1_v4 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 8,
    iOS_GPUFamily2_v4 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 9,
    iOS_GPUFamily3_v3 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 10,
    iOS_GPUFamily4_v1 API_AVAILABLE(ios(11.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 11,

    iOS_GPUFamily1_v5 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 12,
    iOS_GPUFamily2_v5 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 13,
    iOS_GPUFamily3_v4 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 14,
    iOS_GPUFamily4_v2 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 15,
    iOS_GPUFamily5_v1 API_AVAILABLE(ios(12.0)) API_UNAVAILABLE(macos, macCatalyst, tvos) = 16,

    macOS_GPUFamily1_v1 API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macCatalyst) = 10000,
    OSX_GPUFamily1_v1 API_AVAILABLE(macos(10.11)) API_UNAVAILABLE(ios) = macOS_GPUFamily1_v1, // deprecated

    macOS_GPUFamily1_v2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macCatalyst) = 10001,
    OSX_GPUFamily1_v2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = macOS_GPUFamily1_v2, // deprecated
    macOS_ReadWriteTextureTier2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = 10002,
    OSX_ReadWriteTextureTier2 API_AVAILABLE(macos(10.12)) API_UNAVAILABLE(ios) = macOS_ReadWriteTextureTier2, // deprecated

    macOS_GPUFamily1_v3 API_AVAILABLE(macos(10.13)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macCatalyst) = 10003,

    macOS_GPUFamily1_v4 API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macCatalyst) = 10004,
    macOS_GPUFamily2_v1 API_AVAILABLE(macos(10.14)) API_UNAVAILABLE(ios) API_UNAVAILABLE(macCatalyst) = 10005,


    tvOS_GPUFamily1_v1 API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(macos, ios) = 30000,
    TVOS_GPUFamily1_v1 API_AVAILABLE(tvos(9.0)) API_UNAVAILABLE(macos, ios) = tvOS_GPUFamily1_v1, // deprecated

    tvOS_GPUFamily1_v2 API_AVAILABLE(tvos(10.0)) API_UNAVAILABLE(macos, ios) = 30001,

    tvOS_GPUFamily1_v3 API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(macos, ios) = 30002,
    tvOS_GPUFamily2_v1 API_AVAILABLE(tvos(11.0)) API_UNAVAILABLE(macos, ios) = 30003,

    tvOS_GPUFamily1_v4 API_AVAILABLE(tvos(12.0)) API_UNAVAILABLE(macos, ios) = 30004,
    tvOS_GPUFamily2_v2 API_AVAILABLE(tvos(12.0)) API_UNAVAILABLE(macos, ios) = 30005,
} API_DEPRECATED("Use GPUFamily instead", macos(10.11, 13.0), ios(8.0, 16.0), tvos(9.0, 16.0));

enum class GPUFamily: ns::Integer
{
    Apple1  = 1001,
    Apple2  = 1002,
    Apple3  = 1003,
    Apple4  = 1004,
    Apple5  = 1005,
    Apple6  = 1006,
    Apple7  = 1007,
    Apple8  = 1008,

    Mac1 API_DEPRECATED_WITH_REPLACEMENT("Mac2", macos(10.15, 13.0), ios(13.0, 16.0)) = 2001,
    Mac2 = 2002,

    Common1 = 3001,
    Common2 = 3002,
    Common3 = 3003,

    MacCatalyst1 API_DEPRECATED_WITH_REPLACEMENT("Mac2", macos(10.15, 13.0), ios(13.0, 16.0)) = 4001,
    MacCatalyst2 API_DEPRECATED_WITH_REPLACEMENT("Mac2", macos(10.15, 13.0), ios(13.0, 16.0)) = 4002,

    Metal3 API_AVAILABLE(macos(13.0), ios(16.0)) = 5001,
} API_AVAILABLE(macos(10.15), ios(13.0));

enum class DeviceLocation: ns::UInteger
{
    BuiltIn = 0,
    Slot = 1,
    External = 2,
    Unspecified = ns::UIntegerMax,
} API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios);

namespace mtl
{
    class Device final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(name, "name");
        METALPP_PRIVATE_SEL(location, "location");
        METALPP_PRIVATE_SEL(locationNumber, "locationNumber");
        METALPP_PRIVATE_SEL(currentAllocatedSize, "currentAllocatedSize");
        METALPP_PRIVATE_SEL(newCommandQueue, "newCommandQueue");
        METALPP_PRIVATE_SEL(newCommandQueueWithMaxCommandBufferCount_, "newCommandQueueWithMaxCommandBufferCount:");
        METALPP_PRIVATE_SEL(newDepthStencilStateWithDescriptor_, "newDepthStencilStateWithDescriptor:");
        METALPP_PRIVATE_SEL(newBufferWithLength_options_, "newBufferWithLength:options:");
        METALPP_PRIVATE_SEL(newBufferWithBytes_length_options_, "newBufferWithBytes:length:options:");
        METALPP_PRIVATE_SEL(newTextureWithDescriptor_, "newTextureWithDescriptor:");
        METALPP_PRIVATE_SEL(newSamplerStateWithDescriptor_, "newSamplerStateWithDescriptor:");
        METALPP_PRIVATE_SEL(newDefaultLibrary, "newDefaultLibrary");
        METALPP_PRIVATE_SEL(newLibraryWithSource_options_error_, "newLibraryWithSource:options:error:");
        METALPP_PRIVATE_SEL(supportsFeatureSet_, "supportsFeatureSet:");
        METALPP_PRIVATE_SEL(supportsFamily_, "supportsFamily:");
        METALPP_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_error_, "newRenderPipelineStateWithDescriptor:error:");

        using Object::Object;
        
        [[nodiscard]] static auto createSystemDefaultDevice() noexcept
        {
            static const auto mtlCreateSystemDefaultDevice = reinterpret_cast<id(*)()>(dlsym(RTLD_DEFAULT, "MTLCreateSystemDefaultDevice"));
            return Device{mtlCreateSystemDefaultDevice(), ns::adopt};
        }

        Device() = delete;

        [[nodiscard]] auto name() const noexcept
        {
            return getRetained<ns::String>(METALPP_SEL(name));
        }

        [[nodiscard]] auto location() const noexcept API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios)
        {
            return sendMessage<DeviceLocation>(METALPP_SEL(location));
        }

        [[nodiscard]] auto locationNumber() const noexcept API_AVAILABLE(macos(10.15)) API_UNAVAILABLE(ios)
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(locationNumber));
        }

        [[nodiscard]] auto currentAllocatedSize() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(currentAllocatedSize));
        }

        [[nodiscard]] auto newCommandQueue() const noexcept
        {
            const id commandQueue = sendMessage<id>(METALPP_SEL(newCommandQueue));
            return CommandQueue{commandQueue, ns::adopt};
        }

        [[nodiscard]] auto newCommandQueue(const ns::UInteger maxCommandBufferCount) const noexcept
        {
            const id commandQueue = sendMessage<id>(METALPP_SEL(newCommandQueueWithMaxCommandBufferCount_),
                                                    maxCommandBufferCount);
            return CommandQueue{commandQueue, ns::adopt};
        }

        [[nodiscard]] auto newDepthStencilState(const DepthStencilDescriptor& descriptor) const noexcept
        {
            const id depthStencilState = sendMessage<id>(METALPP_SEL(newDepthStencilStateWithDescriptor_),
                                                         descriptor.get());
            return DepthStencilState{depthStencilState, ns::adopt};
        }

        [[nodiscard]] auto newBuffer(const ns::UInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = sendMessage<id>(METALPP_SEL(newBufferWithLength_options_),
                                              length,
                                              options);
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newBuffer(const void* pointer, const ns::UInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = sendMessage<id>(METALPP_SEL(newBufferWithBytes_length_options_),
                                              pointer,
                                              length,
                                              options);
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newTexture(const TextureDescriptor& descriptor) const noexcept
        {
            const id texture = sendMessage<id>(METALPP_SEL(newTextureWithDescriptor_),
                                               descriptor.get());
            return Texture{texture, ns::adopt};
        }

        [[nodiscard]] auto newSamplerState(const SamplerDescriptor& descriptor) const noexcept
        {
            const id samplerState = sendMessage<id>(METALPP_SEL(newSamplerStateWithDescriptor_),
                                                    descriptor.get());
            return SamplerState{samplerState, ns::adopt};
        }

        [[nodiscard]] auto newDefaultLibrary() const noexcept
        {
            const id library = sendMessage<id>(METALPP_SEL(newDefaultLibrary));
            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto newLibrary(const ns::String& source) const
        {
            id error;
            const id library = sendMessage<id>(METALPP_SEL(newLibraryWithSource_options_error_),
                                               source.get(),
                                               nil,
                                               &error);

            if (error != nil)
                throw ns::Error{error};

            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto newLibrary(const ns::String& source, const CompileOptions& compileOptions) const
        {
            id error;
            const id library = sendMessage<id>(METALPP_SEL(newLibraryWithSource_options_error_),
                                               source.get(),
                                               compileOptions.get(),
                                               &error);

            if (error != nil)
                throw ns::Error{error};

            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto supportsFeatureSet(const FeatureSet featureSet) const noexcept API_DEPRECATED("Use supportsFamily instead", macos(10.11, 13.0), ios(8.0, 16.0), tvos(9.0, 16.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsFeatureSet_), featureSet) == YES;
        }

        [[nodiscard]] auto supportsFamily(const GPUFamily gpuFamily) const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsFamily_), gpuFamily) == YES;
        }

        [[nodiscard]] auto newRenderPipelineState(const RenderPipelineDescriptor& renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = sendMessage<id>(METALPP_SEL(newRenderPipelineStateWithDescriptor_error_),
                                                           renderPipelineDescriptor.get(),
                                                           &error);

            if (error != nil)
                throw ns::Error{error};

            return RenderPipelineState{renderPipelineState, ns::adopt};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    [[nodiscard]] inline Device CommandBuffer::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device CommandEncoder::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device CommandQueue::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device DepthStencilState::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device DynamicLibrary::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device Function::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device Library::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device SamplerState::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device RenderPipelineState::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }

    [[nodiscard]] inline Device Resource::device() const noexcept
    {
        return getRetained<Device>(METALPP_SEL(device));
    }
}

#endif
