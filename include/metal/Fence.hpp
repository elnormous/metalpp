#ifndef METALPP_METAL_FENCE_HPP
#define METALPP_METAL_FENCE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"

namespace mtl
{
    class Device;

    class Fence final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");

        using Object::Object;
        using Object::operator=;

        Fence() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }
    } API_AVAILABLE(macos(10.13), ios(10.0));
}

#endif
