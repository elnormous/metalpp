#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include "../objc/Classes.hpp"
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Library.hpp"
#include "PixelFormat.hpp"
#include "VertexDescriptor.hpp"

namespace mtl
{
    class RenderPipelineDescriptor final: public ns::Object
    {
    public:
        RenderPipelineDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::renderPipelineDescriptorClass, objc::allocSel), objc::initSel)}
        {
        }

        ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, objc::labelSel);
            return ns::String{objc::sendMessage<id>(label, objc::retainSel)};
        }

        void setLabel(const ns::String label) noexcept
        {
            objc::sendMessage(*this, objc::setLabel_Sel, static_cast<id>(label));
        }

        mtl::Function vertexFunction() const noexcept
        {
            const id function = objc::sendMessage<id>(*this, objc::vertexFunctionSel);
            return mtl::Function{objc::sendMessage<id>(function, objc::retainSel)};
        }

        void setVertexFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, objc::setVertexFunction_Sel, static_cast<id>(function));
        }

        mtl::Function fragmentFunction() const noexcept
        {
            const id function = objc::sendMessage<id>(*this, objc::fragmentFunctionSel);
            return mtl::Function{objc::sendMessage<id>(function, objc::retainSel)};
        }

        void setFragmentFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, objc::setFragmentFunction_Sel, static_cast<id>(function));
        }

        mtl::VertexDescriptor vertexDescriptor() const noexcept
        {
            const id vertexDescriptor = objc::sendMessage<id>(*this, objc::vertexDescriptorSel);
            return mtl::VertexDescriptor{objc::sendMessage<id>(vertexDescriptor, objc::retainSel)};
        }

        void setVertexDescriptor(const mtl::VertexDescriptor vertexDescriptor) noexcept
        {
            objc::sendMessage(*this, objc::setVertexDescriptor_Sel, static_cast<id>(vertexDescriptor));
        }

        mtl::PixelFormat depthAttachmentPixelFormat() const noexcept
        {
            return objc::sendMessage<mtl::PixelFormat>(*this, objc::depthAttachmentPixelFormatSel);
        }

        void setDepthAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, objc::setDepthAttachmentPixelFormat_Sel, pixelFormat);
        }

        mtl::PixelFormat stencilAttachmentPixelFormat() const noexcept
        {
            return objc::sendMessage<mtl::PixelFormat>(*this, objc::stencilAttachmentPixelFormatSel);
        }

        void setStencilAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, objc::setStencilAttachmentPixelFormat_Sel, pixelFormat);
        }
    };

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState(const id p) noexcept: Object{p} {}
    };
}

#endif
