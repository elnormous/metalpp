#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <dlfcn.h>
#include <type_traits>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
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
#include "Selectors.hpp"
#include "Texture.hpp"

namespace mtl
{
    namespace detail
    {
        inline const auto createSystemDefaultDevice = reinterpret_cast<id (*)()>(dlsym(RTLD_DEFAULT, "MTLCreateSystemDefaultDevice"));
    }

    class Device final: public ns::Object
    {
    public:
        Device(): Object{detail::createSystemDefaultDevice()} {}

        Device(const id p) noexcept: Object{p} {}

        [[nodiscard]] ns::String name() const noexcept
        {
            return getRetained<ns::String>(sel::name);
        }

        [[nodiscard]] CommandQueue newCommandQueue() const noexcept
        {
            const id commandQueue = sendMessage<id>(sel::newCommandQueue);
            return CommandQueue{commandQueue};
        }

        [[nodiscard]] CommandQueue newCommandQueue(const NSUInteger maxCommandBufferCount) const noexcept
        {
            const id commandQueue = sendMessage<id>(sel::newCommandQueueWithMaxCommandBufferCount_,
                                                    maxCommandBufferCount);
            return CommandQueue{commandQueue};
        }

        [[nodiscard]] DepthStencilState newDepthStencilState(const DepthStencilDescriptor& descriptor) const noexcept
        {
            const id depthStencilState = sendMessage<id>(sel::newDepthStencilStateWithDescriptor_,
                                                         static_cast<id>(descriptor));
            return DepthStencilState{depthStencilState};
        }

        [[nodiscard]] Buffer newBuffer(const NSUInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = sendMessage<id>(sel::newBufferWithLength_options_,
                                              length,
                                              options);
            return Buffer{buffer};
        }

        [[nodiscard]] Buffer newBuffer(const void* pointer, const NSUInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = sendMessage<id>(sel::newBufferWithBytes_length_options_,
                                              pointer,
                                              length,
                                              options);
            return Buffer{buffer};
        }

        [[nodiscard]] Texture newTexture(const TextureDescriptor& descriptor) const noexcept
        {
            const id texture = sendMessage<id>(sel::newTextureWithDescriptor_,
                                               static_cast<id>(descriptor));
            return Texture{texture};
        }

        [[nodiscard]] Library newDefaultLibrary() const noexcept
        {
            const id library = sendMessage<id>(sel::newDefaultLibrary);
            return Library{library};
        }

        [[nodiscard]] Library newLibrary(const ns::String& source) const
        {
            id error;
            const id library = sendMessage<id>(sel::newLibraryWithSource_options_error_,
                                               static_cast<id>(source),
                                               nil,
                                               &error);

            if (error != nil)
                throw ns::Error{sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] Library newLibrary(const ns::String& source, const CompileOptions& compileOptions) const
        {
            id error;
            const id library = sendMessage<id>(sel::newLibraryWithSource_options_error_,
                                               static_cast<id>(source),
                                               static_cast<id>(compileOptions),
                                               &error);

            if (error != nil)
                throw ns::Error{sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] RenderPipelineState newRenderPipelineState(const RenderPipelineDescriptor& renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = sendMessage<id>(sel::newRenderPipelineStateWithDescriptor_error_,
                                                           static_cast<id>(renderPipelineDescriptor),
                                                           &error);

            if (error != nil)
                throw ns::Error{sendMessage<id>(error, ns::sel::retain)};

            return RenderPipelineState{renderPipelineState};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    inline Device CommandBuffer::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device CommandEncoder::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device CommandQueue::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device DepthStencilState::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device DynamicLibrary::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device Function::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device Library::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device RenderPipelineState::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    inline Device Resource::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }
}

#endif
