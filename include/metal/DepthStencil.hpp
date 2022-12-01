#ifndef METALPP_METAL_DEPTHSTENCIL_HPP
#define METALPP_METAL_DEPTHSTENCIL_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"
#include "Selectors.hpp"

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

    class DepthStencilDescriptor final: public ns::Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("MTLDepthStencilDescriptor");

        DepthStencilDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] auto label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, label.get());
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class DepthStencilState final: public ns::Object
    {        
    public:
        DepthStencilState() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
