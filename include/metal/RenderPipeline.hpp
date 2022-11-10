#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include "../objc/Object.hpp"
#include "Library.hpp"
#include "PixelFormat.hpp"
#include "VertexDescriptor.hpp"

namespace mtl
{
    class RenderPipelineDescriptor final: public ns::Object
    {
        inline static const auto cls = objc_lookUpClass("MTLRenderPipelineDescriptor");

        inline static const auto setLabelSel = sel_registerName("setLabel:");
        inline static const auto setVertexFunctionSel = sel_registerName("setVertexFunction:");
        inline static const auto setFragmentFunctionSel = sel_registerName("setFragmentFunction:");
        inline static const auto setVertexDescriptorSel = sel_registerName("setVertexDescriptor:");
        inline static const auto setDepthAttachmentPixelFormatSel = sel_registerName("setDepthAttachmentPixelFormat:");
        inline static const auto setStencilAttachmentPixelFormatSel = sel_registerName("setStencilAttachmentPixelFormat:");

    public:
        RenderPipelineDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel), initSel)}
        {
        }

        void setLabel(const ns::String label) noexcept
        {
            objc::sendMessage(*this, setLabelSel, static_cast<id>(label));
        }

        void setVertexFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, setVertexFunctionSel, static_cast<id>(function));
        }

        void setFragmentFunction(const mtl::Function function) noexcept
        {
            objc::sendMessage(*this, setFragmentFunctionSel, static_cast<id>(function));
        }

        void setVertexDescriptor(const mtl::VertexDescriptor vertexDescriptor) noexcept
        {
            objc::sendMessage(*this, setVertexDescriptorSel, static_cast<id>(vertexDescriptor));
        }

        void setDepthAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, setDepthAttachmentPixelFormatSel, pixelFormat);
        }

        void setStencilAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, setStencilAttachmentPixelFormatSel, pixelFormat);
        }
    };

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState(const id p) noexcept: Object{p} {}
    };
}

#endif
