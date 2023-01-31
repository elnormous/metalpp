#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <dlfcn.h>
#include <type_traits>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../dispatch/Data.hpp"
#include "../foundation/Bundle.hpp"
#include "../foundation/Error.hpp"
#include "../foundation/String.hpp"
#include "Buffer.hpp"
#include "CommandBuffer.hpp"
#include "CommandEncoder.hpp"
#include "CommandQueue.hpp"
#include "ComputePipeline.hpp"
#include "DepthStencil.hpp"
#include "DynamicLibrary.hpp"
#include "Event.hpp"
#include "Fence.hpp"
#include "Heap.hpp"
#include "IndirectCommandBuffer.hpp"
#include "Library.hpp"
#include "PixelFormat.hpp"
#include "RenderPipeline.hpp"
#include "Resource.hpp"
#include "Sampler.hpp"
#include "Texture.hpp"

namespace mtl
{
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

    enum class PipelineOption: ns::UInteger
    {
        RenderStagesNone               = 0,
        RenderStagesArgumentInfo       = 1 << 0,
        RenderStagesBufferTypeInfo     = 1 << 1,
        RenderStagesFailOnBinaryArchiveMiss API_AVAILABLE(macos(11.0), ios(14.0)) = 1 << 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    [[nodiscard]] inline constexpr PipelineOption operator&(const PipelineOption a, const PipelineOption b) noexcept
    {
        return static_cast<PipelineOption>(static_cast<std::underlying_type_t<PipelineOption>>(a) & static_cast<std::underlying_type_t<PipelineOption>>(b));
    }
    [[nodiscard]] inline constexpr PipelineOption operator|(const PipelineOption a, const PipelineOption b) noexcept
    {
        return static_cast<PipelineOption>(static_cast<std::underlying_type_t<PipelineOption>>(a) | static_cast<std::underlying_type_t<PipelineOption>>(b));
    }
    [[nodiscard]] inline constexpr PipelineOption operator^(const PipelineOption a, const PipelineOption b) noexcept
    {
        return static_cast<PipelineOption>(static_cast<std::underlying_type_t<PipelineOption>>(a) ^ static_cast<std::underlying_type_t<PipelineOption>>(b));
    }
    [[nodiscard]] inline constexpr PipelineOption operator~(const PipelineOption a) noexcept
    {
        return static_cast<PipelineOption>(~static_cast<std::underlying_type_t<PipelineOption>>(a));
    }
    inline constexpr PipelineOption& operator&=(PipelineOption& a, const PipelineOption b) noexcept
    {
        return a = static_cast<PipelineOption>(static_cast<std::underlying_type_t<PipelineOption>>(a) & static_cast<std::underlying_type_t<PipelineOption>>(b));
    }
    inline constexpr PipelineOption& operator|=(PipelineOption& a, const PipelineOption b) noexcept
    {
        return a = static_cast<PipelineOption>(static_cast<std::underlying_type_t<PipelineOption>>(a) | static_cast<std::underlying_type_t<PipelineOption>>(b));
    }
    inline constexpr PipelineOption& operator^=(PipelineOption& a, const PipelineOption b) noexcept
    {
        return a = static_cast<PipelineOption>(static_cast<std::underlying_type_t<PipelineOption>>(a) ^ static_cast<std::underlying_type_t<PipelineOption>>(b));
    }

    enum class CounterSamplingPoint: ns::UInteger
    {
        AtStageBoundary,
        AtDrawBoundary,
        AtDispatchBoundary,
        AtTileDispatchBoundary,
        AtBlitBoundary
    } API_AVAILABLE(macos(11.0), ios(14.0));

    enum class SparsePageSize: ns::Integer
    {
        Size16 = 101,
        Size64 = 102,
        Size256 = 103,
    } API_AVAILABLE(macos(13.0), ios(16.0));

    struct SizeAndAlign
    {
        ns::UInteger size;
        ns::UInteger align;
    };

    class Device final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(name, "name");
        METALPP_PRIVATE_SEL(location, "location");
        METALPP_PRIVATE_SEL(locationNumber, "locationNumber");
        METALPP_PRIVATE_SEL(currentAllocatedSize, "currentAllocatedSize");
        METALPP_PRIVATE_SEL(newCommandQueue, "newCommandQueue");
        METALPP_PRIVATE_SEL(newCommandQueueWithMaxCommandBufferCount_, "newCommandQueueWithMaxCommandBufferCount:");
        METALPP_PRIVATE_SEL(heapTextureSizeAndAlignWithDescriptor_, "heapTextureSizeAndAlignWithDescriptor:");
        METALPP_PRIVATE_SEL(heapBufferSizeAndAlignWithLength_options_, "heapBufferSizeAndAlignWithLength:options:");
        METALPP_PRIVATE_SEL(newHeapWithDescriptor_, "newHeapWithDescriptor:");
        METALPP_PRIVATE_SEL(newBufferWithLength_options_, "newBufferWithLength:options:");
        METALPP_PRIVATE_SEL(newBufferWithBytes_length_options_, "newBufferWithBytes:length:options:");
        METALPP_PRIVATE_SEL(newBufferWithBytesNoCopy_length_options_deallocator_, "newBufferWithBytesNoCopy:length:options:deallocator:");
        METALPP_PRIVATE_SEL(newDepthStencilStateWithDescriptor_, "newDepthStencilStateWithDescriptor:");
        METALPP_PRIVATE_SEL(newTextureWithDescriptor_, "newTextureWithDescriptor:");
        METALPP_PRIVATE_SEL(newSamplerStateWithDescriptor_, "newSamplerStateWithDescriptor:");
        METALPP_PRIVATE_SEL(newDefaultLibrary, "newDefaultLibrary");
        METALPP_PRIVATE_SEL(newDefaultLibraryWithBundle_error_, "newDefaultLibraryWithBundle:error:");
        METALPP_PRIVATE_SEL(newLibraryWithData_error_, "newLibraryWithData:error:");
        METALPP_PRIVATE_SEL(newLibraryWithSource_options_error_, "newLibraryWithSource:options:error:");
        METALPP_PRIVATE_SEL(newRenderPipelineStateWithDescriptor_error_, "newRenderPipelineStateWithDescriptor:error:");
        METALPP_PRIVATE_SEL(newComputePipelineStateWithFunction_error_, "newComputePipelineStateWithFunction:error:");
        METALPP_PRIVATE_SEL(newFence, "newFence");
        METALPP_PRIVATE_SEL(supportsFeatureSet_, "supportsFeatureSet:");
        METALPP_PRIVATE_SEL(supportsFamily_, "supportsFamily:");
        METALPP_PRIVATE_SEL(supportsTextureSampleCount_, "supportsTextureSampleCount:");
        METALPP_PRIVATE_SEL(minimumLinearTextureAlignmentForPixelFormat_, "minimumLinearTextureAlignmentForPixelFormat:");
        METALPP_PRIVATE_SEL(minimumTextureBufferAlignmentForPixelFormat_, "minimumTextureBufferAlignmentForPixelFormat:");
        METALPP_PRIVATE_SEL(newIndirectCommandBufferWithDescriptor_maxCommandCount_options_, "newIndirectCommandBufferWithDescriptor:maxCommandCount:options:");
        METALPP_PRIVATE_SEL(newEvent, "newEvent");
        METALPP_PRIVATE_SEL(maxBufferLength, "maxBufferLength");
        METALPP_PRIVATE_SEL(supportsCounterSampling_, "supportsCounterSampling:");
        METALPP_PRIVATE_SEL(supportsVertexAmplificationCount_, "supportsVertexAmplificationCount:");
        METALPP_PRIVATE_SEL(supportsDynamicLibraries, "supportsDynamicLibraries");
        METALPP_PRIVATE_SEL(supportsRenderDynamicLibraries, "supportsRenderDynamicLibraries");
        METALPP_PRIVATE_SEL(supportsRaytracing, "supportsRaytracing");
        METALPP_PRIVATE_SEL(supportsFunctionPointers, "supportsFunctionPointers");
        METALPP_PRIVATE_SEL(supportsFunctionPointersFromRender, "supportsFunctionPointersFromRender");
        METALPP_PRIVATE_SEL(supportsRaytracingFromRender, "supportsRaytracingFromRender");
        METALPP_PRIVATE_SEL(supportsPrimitiveMotionBlur, "supportsPrimitiveMotionBlur");

        using Object::Object;
        using Object::operator=;
        
        [[nodiscard]] static auto createSystemDefaultDevice() noexcept
        {
            static const auto mtlCreateSystemDefaultDevice = reinterpret_cast<id(*)()>(dlsym(RTLD_DEFAULT, "MTLCreateSystemDefaultDevice"));
            return Device{mtlCreateSystemDefaultDevice(), ns::adopt};
        }

        Device() = delete;

        [[nodiscard]] auto name() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(name))};
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

        [[nodiscard]] auto newCommandQueue() noexcept
        {
            const id commandQueue = sendMessage<id>(METALPP_SEL(newCommandQueue));
            return CommandQueue{commandQueue, ns::adopt};
        }

        [[nodiscard]] auto newCommandQueue(const ns::UInteger maxCommandBufferCount) noexcept
        {
            const id commandQueue = sendMessage<id>(METALPP_SEL(newCommandQueueWithMaxCommandBufferCount_),
                                                    maxCommandBufferCount);
            return CommandQueue{commandQueue, ns::adopt};
        }

        [[nodiscard]] auto heapTextureSizeAndAlign(const TextureDescriptor& desc) const noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            return sendMessage<SizeAndAlign>(METALPP_SEL(heapTextureSizeAndAlignWithDescriptor_), desc.get());
        }

        [[nodiscard]] auto heapBufferSizeAndAlign(const ns::UInteger length, const ResourceOptions options) const noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            return sendMessage<SizeAndAlign>(METALPP_SEL(heapBufferSizeAndAlignWithLength_options_), length, options);
        }

        [[nodiscard]] auto newHeap(const HeapDescriptor& descriptor) API_AVAILABLE(macos(10.13), ios(10.0))
        {
            const id heap = sendMessage<id>(METALPP_SEL(newHeapWithDescriptor_),
                                            descriptor.get());
            return Heap{heap, ns::adopt};
        }

        [[nodiscard]] auto newBuffer(const ns::UInteger length, const ResourceOptions options) noexcept
        {
            const id buffer = sendMessage<id>(METALPP_SEL(newBufferWithLength_options_),
                                              length,
                                              options);
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newBuffer(const void* pointer, const ns::UInteger length, const ResourceOptions options) noexcept
        {
            const id buffer = sendMessage<id>(METALPP_SEL(newBufferWithBytes_length_options_),
                                              pointer,
                                              length,
                                              options);
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newBuffer(const void* pointer, const ns::UInteger length, const ResourceOptions options, const std::function<void(void* pointer, ns::UInteger length)> deallocator) noexcept
        {
            const id buffer = sendMessage<id>(METALPP_SEL(newBufferWithBytesNoCopy_length_options_deallocator_),
                                              pointer,
                                              length,
                                              options,
                                              ^(void* p, NSUInteger l) { deallocator(p, l); });
            return Buffer{buffer, ns::adopt};
        }

        [[nodiscard]] auto newDepthStencilState(const DepthStencilDescriptor& descriptor) noexcept
        {
            const id depthStencilState = sendMessage<id>(METALPP_SEL(newDepthStencilStateWithDescriptor_),
                                                         descriptor.get());
            return DepthStencilState{depthStencilState, ns::adopt};
        }

        [[nodiscard]] auto newTexture(const TextureDescriptor& descriptor) noexcept
        {
            const id texture = sendMessage<id>(METALPP_SEL(newTextureWithDescriptor_),
                                               descriptor.get());
            return Texture{texture, ns::adopt};
        }

        [[nodiscard]] auto newSamplerState(const SamplerDescriptor& descriptor) noexcept
        {
            const id samplerState = sendMessage<id>(METALPP_SEL(newSamplerStateWithDescriptor_),
                                                    descriptor.get());
            return SamplerState{samplerState, ns::adopt};
        }

        [[nodiscard]] auto newDefaultLibrary() noexcept
        {
            const id library = sendMessage<id>(METALPP_SEL(newDefaultLibrary));
            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto newDefaultLibrary(const ns::Bundle& bundle) API_AVAILABLE(macos(10.12), ios(10.0))
        {
            id error = nil;
            const id library = sendMessage<id>(METALPP_SEL(newDefaultLibraryWithBundle_error_),
                                               bundle.get(),
                                               &error);

            if (error != nil)
                throw ns::Error{error};

            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto newLibrary(const dispatch::Data& data)
        {
            id error = nil;
            const id library = sendMessage<id>(METALPP_SEL(newLibraryWithData_error_),
                                               data.get(),
                                               &error);

            if (error != nil)
                throw ns::Error{error};

            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto newLibrary(const ns::String& source, const CompileOptions& compileOptions)
        {
            id error = nil;
            const id library = sendMessage<id>(METALPP_SEL(newLibraryWithSource_options_error_),
                                               source.get(),
                                               compileOptions.get(),
                                               &error);

            if (error != nil)
                throw ns::Error{error};

            return Library{library, ns::adopt};
        }

        [[nodiscard]] auto newRenderPipelineState(const RenderPipelineDescriptor& renderPipelineDescriptor)
        {
            id error = nil;
            const id renderPipelineState = sendMessage<id>(METALPP_SEL(newRenderPipelineStateWithDescriptor_error_),
                                                           renderPipelineDescriptor.get(),
                                                           &error);

            if (error != nil)
                throw ns::Error{error};

            return RenderPipelineState{renderPipelineState, ns::adopt};
        }

        [[nodiscard]] auto newComputePipelineState(const Function& computeFunction)
        {
            id error = nil;
            const id renderPipelineState = sendMessage<id>(METALPP_SEL(newComputePipelineStateWithFunction_error_),
                                                           computeFunction.get(),
                                                           &error);

            if (error != nil)
                throw ns::Error{error};

            return ComputePipelineState{renderPipelineState, ns::adopt};
        }

        [[nodiscard]] auto newFence() API_AVAILABLE(macos(10.13), ios(10.0))
        {
            const id fence = sendMessage<id>(METALPP_SEL(newFence));
            return Fence{fence, ns::adopt};
        }

        [[nodiscard]] auto supportsFeatureSet(const FeatureSet featureSet) const noexcept API_DEPRECATED("Use supportsFamily instead", macos(10.11, 13.0), ios(8.0, 16.0), tvos(9.0, 16.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsFeatureSet_), featureSet) == YES;
        }

        [[nodiscard]] auto supportsFamily(const GPUFamily gpuFamily) const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsFamily_), gpuFamily) == YES;
        }

        [[nodiscard]] auto supportsTextureSampleCount(const ns::UInteger sampleCount) const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsTextureSampleCount_), sampleCount) == YES;
        }

        [[nodiscard]] auto minimumLinearTextureAlignment(const PixelFormat format) const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return sendMessage<ns::Integer>(METALPP_SEL(minimumLinearTextureAlignmentForPixelFormat_), format);
        }

        [[nodiscard]] auto minimumTextureBufferAlignment(const PixelFormat format) const noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            return sendMessage<ns::Integer>(METALPP_SEL(minimumTextureBufferAlignmentForPixelFormat_), format);
        }

        [[nodiscard]] auto newIndirectCommandBuffer(const IndirectCommandBufferDescriptor& descriptor, const ns::UInteger maxCount, const ResourceOptions options) API_AVAILABLE(macos(10.14), ios(12.0))
        {
            const id indirectCommandBuffer = sendMessage<id>(METALPP_SEL(newIndirectCommandBufferWithDescriptor_maxCommandCount_options_),
                                                             descriptor.get(),
                                                             maxCount,
                                                             options);
            return IndirectCommandBuffer{indirectCommandBuffer};
        }

        [[nodiscard]] auto newEvent() API_AVAILABLE(macos(10.14), ios(12.0))
        {
            const id event = sendMessage<id>(METALPP_SEL(newEvent));
            return Event{event, ns::adopt};
        }

        [[nodiscard]] auto maxBufferLength() const noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxBufferLength));
        }

        [[nodiscard]] auto supportsCounterSampling(const CounterSamplingPoint samplingPoint) const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsCounterSampling_), samplingPoint) == YES;
        }

        [[nodiscard]] auto supportsVertexAmplificationCount(const ns::UInteger count) noexcept API_AVAILABLE(macos(10.15.4), ios(13.0), macCatalyst(13.4))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsVertexAmplificationCount_), count);
        }

        [[nodiscard]] auto supportsDynamicLibraries() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsDynamicLibraries)) == YES;
        }

        [[nodiscard]] auto supportsRenderDynamicLibraries() const noexcept API_AVAILABLE(macos(12.0), ios(15.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsRenderDynamicLibraries)) == YES;
        }

        [[nodiscard]] auto supportsRaytracing() const noexcept  API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsRaytracing)) == YES;
        }

        [[nodiscard]] auto supportsFunctionPointers() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsFunctionPointers)) == YES;
        }

        [[nodiscard]] auto supportsFunctionPointersFromRender() const noexcept API_AVAILABLE(macos(12.0), ios(15.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsFunctionPointersFromRender)) == YES;
        }

        [[nodiscard]] auto supportsRaytracingFromRender() const noexcept API_AVAILABLE(macos(12.0), ios(15.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsRaytracingFromRender)) == YES;
        }

        [[nodiscard]] auto supportsPrimitiveMotionBlur() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(supportsPrimitiveMotionBlur)) == YES;
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    [[nodiscard]] inline Device CommandBuffer::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device CommandEncoder::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device ComputePipelineState::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device CommandQueue::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device DepthStencilState::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device DynamicLibrary::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device Event::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device Fence::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device Function::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device Heap::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device Library::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device SamplerState::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device RenderPipelineState::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }

    [[nodiscard]] inline Device Resource::device() const noexcept
    {
        return Device{sendMessage<id>(METALPP_SEL(device))};
    }
}

#endif
