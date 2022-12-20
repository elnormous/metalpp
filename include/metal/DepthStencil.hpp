#ifndef METALPP_METAL_DEPTHSTENCIL_HPP
#define METALPP_METAL_DEPTHSTENCIL_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class Device;

    enum class CompareFunction: ns::UInteger
    {
        Never = 0,
        Less = 1,
        Equal = 2,
        LessEqual = 3,
        Greater = 4,
        NotEqual = 5,
        GreaterEqual = 6,
        Always = 7,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StencilOperation: ns::UInteger
    {
        Keep = 0,
        Zero = 1,
        Replace = 2,
        IncrementClamp = 3,
        DecrementClamp = 4,
        Invert = 5,
        IncrementWrap = 6,
        DecrementWrap = 7,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class StencilDescriptor final: public ns::Object
    {
    public:
        static constexpr bool copying = true;
    };

    class DepthStencilDescriptor final: public ns::Object
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLDepthStencilDescriptor");

        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");

        DepthStencilDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class DepthStencilState final: public ns::Object
    {        
    public:
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(label, "label");

        using Object::Object;

        DepthStencilState() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
