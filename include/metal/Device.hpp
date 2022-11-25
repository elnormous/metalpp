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
        static Device createSystemDefaultDevice() noexcept
        {
            return Device{detail::createSystemDefaultDevice()};
        }

        Device() = delete;

        [[nodiscard]] auto name() const noexcept
        {
            return getRetained<ns::String>(sel::name);
        }

        [[nodiscard]] auto newCommandQueue() const noexcept
        {
            const id commandQueue = sendMessage<id>(sel::newCommandQueue);
            return CommandQueue{commandQueue};
        }

        [[nodiscard]] auto newCommandQueue(const ns::UInteger maxCommandBufferCount) const noexcept
        {
            const id commandQueue = sendMessage<id>(sel::newCommandQueueWithMaxCommandBufferCount_,
                                                    maxCommandBufferCount);
            return CommandQueue{commandQueue};
        }

        [[nodiscard]] auto newDepthStencilState(const DepthStencilDescriptor& descriptor) const noexcept
        {
            const id depthStencilState = sendMessage<id>(sel::newDepthStencilStateWithDescriptor_,
                                                         static_cast<id>(descriptor));
            return DepthStencilState{depthStencilState};
        }

        [[nodiscard]] auto newBuffer(const ns::UInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = sendMessage<id>(sel::newBufferWithLength_options_,
                                              length,
                                              options);
            return Buffer{buffer};
        }

        [[nodiscard]] auto newBuffer(const void* pointer, const ns::UInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = sendMessage<id>(sel::newBufferWithBytes_length_options_,
                                              pointer,
                                              length,
                                              options);
            return Buffer{buffer};
        }

        [[nodiscard]] auto newTexture(const TextureDescriptor& descriptor) const noexcept
        {
            const id texture = sendMessage<id>(sel::newTextureWithDescriptor_,
                                               static_cast<id>(descriptor));
            return Texture{texture};
        }

        [[nodiscard]] auto newDefaultLibrary() const noexcept
        {
            const id library = sendMessage<id>(sel::newDefaultLibrary);
            return Library{library};
        }

        [[nodiscard]] auto newLibrary(const ns::String& source) const
        {
            id error;
            const id library = sendMessage<id>(sel::newLibraryWithSource_options_error_,
                                               static_cast<id>(source),
                                               nil,
                                               &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] auto newLibrary(const ns::String& source, const CompileOptions& compileOptions) const
        {
            id error;
            const id library = sendMessage<id>(sel::newLibraryWithSource_options_error_,
                                               static_cast<id>(source),
                                               static_cast<id>(compileOptions),
                                               &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] auto newRenderPipelineState(const RenderPipelineDescriptor& renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = sendMessage<id>(sel::newRenderPipelineStateWithDescriptor_error_,
                                                           static_cast<id>(renderPipelineDescriptor),
                                                           &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return RenderPipelineState{renderPipelineState};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    [[nodiscard]] inline Device CommandBuffer::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device CommandEncoder::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device CommandQueue::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device DepthStencilState::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device DynamicLibrary::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device Function::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device Library::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device RenderPipelineState::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }

    [[nodiscard]] inline Device Resource::device() const noexcept
    {
        return getRetained<Device>(sel::device);
    }
}

#endif
