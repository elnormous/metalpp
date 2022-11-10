#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include "../objc/Object.hpp"

namespace mtl
{
    inline namespace detail
    {
        inline const Class renderPipelineDescriptorClass = objc_lookUpClass("MTLRenderPipelineDescriptor");

        inline const auto setLabelSel = sel_registerName("setLabel:");
    }

    class RenderPipelineDescriptor final: public ns::Object
    {
    public:
        RenderPipelineDescriptor():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(renderPipelineDescriptorClass, ns::allocSel), ns::initSel)}
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
