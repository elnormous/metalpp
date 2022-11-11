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
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::depthStencilDescriptorClass, objc::sel::alloc), objc::sel::init)}
        {
        }
    };

    class DepthStencilState final: public ns::Object
    {        
    public:
        ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, objc::sel::label);
            return ns::String{objc::sendMessage<id>(label, objc::sel::retain)};
        }
    };
}

#endif
