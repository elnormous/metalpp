#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include "../objc/Object.hpp"

namespace mtl
{
    class RenderPipelineDescriptor final: public ns::Object
    {
        inline static const Class cls = objc_lookUpClass("MTLRenderPipelineDescriptor");

        inline static const auto setLabelSel = sel_registerName("setLabel:");

    public:
        RenderPipelineDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel), initSel)}
        {
        }

        void setLabel(const ns::String label) noexcept
        {
            id function = objc::sendMessage<id>(*this,
                                                setLabelSel,
                                                static_cast<id>(label));
        }
    };

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState(const id p) noexcept: Object{p}
        {
            if (p) objc::sendMessage(p, retainSel);
        }
    };
}

#endif
