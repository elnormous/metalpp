#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include "../objc/Classes.hpp"
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Library.hpp"
#include "PixelFormat.hpp"
#include "Selectors.hpp"
#include "VertexDescriptor.hpp"

namespace mtl
{
    class RenderPipelineDescriptor final: public ns::Object
    {
    public:
        RenderPipelineDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::renderPipelineDescriptorClass, ns::sel::alloc), ns::sel::init)}
        {
        }

        ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }

        mtl::Function vertexFunction() const noexcept
        {
            const id function = objc::sendMessage<id>(*this, sel::vertexFunction);
            return mtl::Function{objc::sendMessage<id>(function, ns::sel::retain)};
        }

        void setVertexFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, sel::setVertexFunction_, static_cast<id>(function));
        }

        mtl::Function fragmentFunction() const noexcept
        {
            const id function = objc::sendMessage<id>(*this, sel::fragmentFunction);
            return mtl::Function{objc::sendMessage<id>(function, ns::sel::retain)};
        }

        void setFragmentFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, sel::setFragmentFunction_, static_cast<id>(function));
        }

        mtl::VertexDescriptor vertexDescriptor() const noexcept
        {
            const id vertexDescriptor = objc::sendMessage<id>(*this, sel::vertexDescriptor);
            return mtl::VertexDescriptor{objc::sendMessage<id>(vertexDescriptor, ns::sel::retain)};
        }

        void setVertexDescriptor(const mtl::VertexDescriptor vertexDescriptor) noexcept
        {
            objc::sendMessage(*this, sel::setVertexDescriptor_, static_cast<id>(vertexDescriptor));
        }

        mtl::PixelFormat depthAttachmentPixelFormat() const noexcept
        {
            return objc::sendMessage<mtl::PixelFormat>(*this, sel::depthAttachmentPixelFormat);
        }

        void setDepthAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, sel::setDepthAttachmentPixelFormat_, pixelFormat);
        }

        mtl::PixelFormat stencilAttachmentPixelFormat() const noexcept
        {
            return objc::sendMessage<mtl::PixelFormat>(*this, sel::stencilAttachmentPixelFormat);
        }

        void setStencilAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, sel::setStencilAttachmentPixelFormat_, pixelFormat);
        }
    };

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState(const id p) noexcept: Object{p} {}
    };
}

#endif
