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

        void setLabel(const ns::String label) noexcept
        {
            objc::sendMessage(*this, objc::setLabel_Sel, static_cast<id>(label));
        }

        void setVertexFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, objc::setVertexFunction_Sel, static_cast<id>(function));
        }

        void setFragmentFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, objc::setFragmentFunction_Sel, static_cast<id>(function));
        }

        void setVertexDescriptor(const mtl::VertexDescriptor vertexDescriptor) noexcept
        {
            objc::sendMessage(*this, objc::setVertexDescriptor_Sel, static_cast<id>(vertexDescriptor));
        }

        void setDepthAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, objc::setDepthAttachmentPixelFormat_Sel, pixelFormat);
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
