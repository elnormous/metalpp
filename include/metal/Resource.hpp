#ifndef METALPP_METAL_RESOURCE_HPP
#define METALPP_METAL_RESOURCE_HPP

#include "../objc/Object.hpp"
#include "../foundation/String.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    class Resource: public ns::Object
    {
    public:
        Resource(const id p) noexcept: Object{p} {}

        Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String& label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }
    };
}

#endif