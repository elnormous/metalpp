#ifndef METALPP_METAL_DEPTHSTENCIL_HPP
#define METALPP_METAL_DEPTHSTENCIL_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    class DepthStencilDescriptor final: public ns::Object
    {
    public:
        DepthStencilDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(mtl::cls::depthStencilDescriptor, ns::sel::alloc), ns::sel::init)}
        {
        }
    };

    class DepthStencilState final: public ns::Object
    {        
    public:
        Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }
    };
}

#endif
