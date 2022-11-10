#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include "../objc/Object.hpp"

namespace mtl
{
    class RenderPipelineDescriptor final: public ns::Object
    {
        inline static const Class cls = objc_lookUpClass("MTLRenderPipelineDescriptor");

        inline static const auto allocSel = sel_registerName("alloc");
        inline static const auto initSel = sel_registerName("init");
        inline static const auto setLabelSel = sel_registerName("setLabel:");

    public:
        RenderPipelineDescriptor():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel),
                                         initSel), false}
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
        using Object::Object;
    };
}

#endif
