#ifndef METALPP_METAL_DEPTHSTENCIL_HPP
#define METALPP_METAL_DEPTHSTENCIL_HPP

#include "../objc/Classes.hpp"
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class DepthStencilDescriptor final: public ns::Object
    {
    public:
        DepthStencilDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::depthStencilDescriptorClass, objc::allocSel), objc::initSel)}
        {
        }
    };

    class DepthStencilState final: public ns::Object
    {        
    public:
        ns::String label() noexcept
        {
            const id label = objc::sendMessage<id>(*this, objc::labelSel);
            return ns::String{objc::sendMessage<id>(label, objc::retainSel)};
        }
    };
}

#endif
