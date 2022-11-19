#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

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

extern "C" id MTLCreateSystemDefaultDevice();

namespace mtl
{
    class Device final: public ns::Object
    {
    public:
        Device(): Object{MTLCreateSystemDefaultDevice()} {}

        Device(const id p) noexcept: Object{p} {}

        [[nodiscard]] ns::String name() const noexcept
        {
            const id name = objc::sendMessage<id>(*this, sel::name);
            return ns::String{objc::sendMessage<id>(name, ns::sel::retain)};
        }

        [[nodiscard]] CommandQueue newCommandQueue() const noexcept
        {
            const id commandQueue = objc::sendMessage<id>(*this, sel::newCommandQueue);
            return CommandQueue{commandQueue};
        }

        [[nodiscard]] CommandQueue newCommandQueue(const NSUInteger maxCommandBufferCount) const noexcept
        {
            const id commandQueue = objc::sendMessage<id>(*this,
                                                          sel::newCommandQueueWithMaxCommandBufferCount_,
                                                          maxCommandBufferCount);
            return CommandQueue{commandQueue};
        }

        [[nodiscard]] DepthStencilState newDepthStencilState(const DepthStencilDescriptor& descriptor) const noexcept
        {
            const id depthStencilState = objc::sendMessage<id>(*this,
                                                               sel::newDepthStencilStateWithDescriptor_,
                                                               static_cast<id>(descriptor));
            return DepthStencilState{depthStencilState};
        }

        [[nodiscard]] Buffer newBuffer(const NSUInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = objc::sendMessage<id>(*this,
                                                    sel::newBufferWithLength_options_,
                                                    length,
                                                    options);
            return Buffer{buffer};
        }

        [[nodiscard]] Buffer newBuffer(const void* pointer, const NSUInteger length, const ResourceOptions options) const noexcept
        {
            const id buffer = objc::sendMessage<id>(*this,
                                                    sel::newBufferWithBytes_length_options_,
                                                    pointer,
                                                    length,
                                                    options);
            return Buffer{buffer};
        }

        [[nodiscard]] Texture newTexture(const TextureDescriptor& descriptor) const noexcept
        {
            const id texture = objc::sendMessage<id>(*this,
                                                     sel::newTextureWithDescriptor_,
                                                     static_cast<id>(descriptor));
            return Texture{texture};
        }

        [[nodiscard]] Library newDefaultLibrary() const noexcept
        {
            const id library = objc::sendMessage<id>(*this, sel::newDefaultLibrary);
            return Library{library};
        }

        [[nodiscard]] Library newLibrary(const ns::String& source) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     sel::newLibraryWithSource_options_error_,
                                                     static_cast<id>(source),
                                                     nil,
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] Library newLibrary(const ns::String& source, const CompileOptions& compileOptions) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     sel::newLibraryWithSource_options_error_,
                                                     static_cast<id>(source),
                                                     static_cast<id>(compileOptions),
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] RenderPipelineState newRenderPipelineState(const RenderPipelineDescriptor& renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = objc::sendMessage<id>(*this,
                                                                 sel::newRenderPipelineStateWithDescriptor_error_,
                                                                 static_cast<id>(renderPipelineDescriptor),
                                                                 &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return RenderPipelineState{renderPipelineState};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    inline Device CommandBuffer::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device CommandEncoder::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device CommandQueue::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device DepthStencilState::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device DynamicLibrary::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device Function::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device Library::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device RenderPipelineState::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }

    inline Device Resource::device() const noexcept
    {
        const id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }
}

#endif
