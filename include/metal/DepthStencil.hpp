#ifndef METALPP_METAL_DEPTHSTENCIL_HPP
#define METALPP_METAL_DEPTHSTENCIL_HPP

#include "../objc/Object.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class DepthStencilDescriptor final: public ns::Object
    {
        inline static const auto cls = objc_lookUpClass("MTLDepthStencilDescriptor");

    public:
        DepthStencilDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel), initSel)}
        {
        }
    };

    class DepthStencilState final: public ns::Object
    {
        inline static const auto labelSel = sel_registerName("label");
        
    public:
        ns::String label() noexcept
        {
            const id label = objc::sendMessage<id>(*this, labelSel);
            return ns::String{objc::sendMessage<id>(label, retainSel)};
        }
    };
}

#endif
