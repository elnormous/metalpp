#ifndef METALPP_METAL_FUNCTIONCONSTANTVALUES_HPP
#define METALPP_METAL_FUNCTIONCONSTANTVALUES_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "../foundation/Range.hpp"
#include "../foundation/String.hpp"
#include "Argument.hpp"

namespace mtl
{
    class FunctionConstantValues final: public ns::Object
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLFunctionConstantValues");

        METALPP_PRIVATE_SEL(setConstantValue_type_atIndex_, "setConstantValue:type:atIndex:");
        METALPP_PRIVATE_SEL(setConstantValues_type_withRange_, "setConstantValues:type:withRange:");
        METALPP_PRIVATE_SEL(setConstantValue_type_withName_, "setConstantValue:type:withName:");

        using Object::Object;
        using Object::operator=;

        FunctionConstantValues() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        void setConstantValue(const void* value, const DataType type, const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setConstantValue_type_atIndex_), value, type, index);
        }

        void setConstantValues(const void* values, const DataType type, const ns::Range range) noexcept
        {
            sendMessage(METALPP_SEL(setConstantValues_type_withRange_), values, type, range);
        }

        void setConstantValue(const void* value, const DataType type, const ns::String name) noexcept
        {
            sendMessage(METALPP_SEL(setConstantValue_type_withName_), value, type, name.get());
        }

    } API_AVAILABLE(macos(10.12), ios(10.0));
}

#endif
