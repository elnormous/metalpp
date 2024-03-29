#ifndef METALPP_METAL_COMPUTEPIPELINE_HPP
#define METALPP_METAL_COMPUTEPIPELINE_HPP

#include "../objc/Object.hpp"
#include "../foundation/Object.hpp"
#include "Library.hpp"
#include "Types.hpp"

namespace mtl
{
    class Device;

    class ComputePipelineDescriptor final: public ns::Object, public ns::Copying
    {
    public:
        METALPP_PRIVATE_CLS("MTLComputePipelineDescriptor");

        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(computeFunction, "computeFunction");
        METALPP_PRIVATE_SEL(setComputeFunction_, "setComputeFunction:");

        using Object::Object;
        using Object::operator=;

        ComputePipelineDescriptor() noexcept:
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

        [[nodiscard]] auto computeFunction() const noexcept
        {
            return Function{sendMessage<id>(METALPP_SEL(computeFunction))};
        }

        void setComputeFunction(const Function& computeFunction) const noexcept
        {
            sendMessage(METALPP_SEL(setComputeFunction_), computeFunction.get());
        }
    } API_AVAILABLE(macos(10.11), ios(9.0));

    class ComputePipelineState final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(maxTotalThreadsPerThreadgroup, "maxTotalThreadsPerThreadgroup");
        METALPP_PRIVATE_SEL(threadExecutionWidth, "threadExecutionWidth");
        METALPP_PRIVATE_SEL(gpuResourceID, "gpuResourceID");
        
        using Object::Object;
        using Object::operator=;

        ComputePipelineState() = delete;

        [[nodiscard]] auto label() const noexcept API_AVAILABLE(macos(10.13), ios(11.0))
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto maxTotalThreadsPerThreadgroup() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(maxTotalThreadsPerThreadgroup));
        }

        [[nodiscard]] auto threadExecutionWidth() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(threadExecutionWidth));
        }

        [[nodiscard]] auto gpuResourceID() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<ResourceID>(METALPP_SEL(gpuResourceID));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
