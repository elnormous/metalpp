#ifndef METALPP_METAL_COMPUTEPIPELINE_HPP
#define METALPP_METAL_COMPUTEPIPELINE_HPP

#include "../objc/Object.hpp"

namespace mtl
{
    class Device;

    class ComputePipelineDescriptor final: public ns::Object
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLComputePipelineDescriptor");

        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");

        using Object::Object;
        using Object::operator=;

        ComputePipelineDescriptor():
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

    } API_AVAILABLE(macos(10.11), ios(9.0));

    class ComputePipelineState final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(device, "device");
        
        using Object::Object;
        using Object::operator=;

        ComputePipelineState() = delete;

        [[nodiscard]] auto label() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        [[nodiscard]] Device device() const noexcept;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
