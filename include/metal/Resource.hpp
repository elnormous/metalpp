#ifndef METALPP_METAL_RESOURCE_HPP
#define METALPP_METAL_RESOURCE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../foundation/String.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    class Resource: public ns::Object
    {
    public:
        Resource() = delete;

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
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
