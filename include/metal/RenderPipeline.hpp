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
            objc::sendMessage(*this, objc::setLabelSel, static_cast<id>(label));
        }

        void setVertexFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, objc::setVertexFunctionSel, static_cast<id>(function));
        }

        void setFragmentFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, objc::setFragmentFunctionSel, static_cast<id>(function));
        }

        void setVertexDescriptor(const mtl::VertexDescriptor vertexDescriptor) noexcept
        {
            objc::sendMessage(*this, objc::setVertexDescriptorSel, static_cast<id>(vertexDescriptor));
        }

        void setDepthAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, objc::setDepthAttachmentPixelFormatSel, pixelFormat);
        }

        void setStencilAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, objc::setStencilAttachmentPixelFormatSel, pixelFormat);
        }
    };

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState(const id p) noexcept: Object{p} {}
    };
}

#endif
