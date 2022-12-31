#ifndef METALPP_FOUNDATION_VALUE_HPP
#define METALPP_FOUNDATION_VALUE_HPP

#include "../objc/Object.hpp"

namespace ns
{
    class Value: public Object
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("NSValue");
        METALPP_PRIVATE_SEL(initWithBytes_objCType_, "initWithBytes:objCType:");

        using Object::Object;
        using Object::operator=;

        Value() = delete;

        Value(const void* value, const char* type):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithBytes_objCType_), value, type), adopt}
        {
        }
    };

    class Number: public Value
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("NSNumber");

        METALPP_PRIVATE_SEL(initWithChar_, "initWithChar:");
        METALPP_PRIVATE_SEL(initWithUnsignedChar_, "initWithUnsignedChar:");
        METALPP_PRIVATE_SEL(initWithShort_, "initWithShort:");
        METALPP_PRIVATE_SEL(initWithUnsignedShort_, "initWithUnsignedShort:");
        METALPP_PRIVATE_SEL(initWithInt_, "initWithInt:");
        METALPP_PRIVATE_SEL(initWithUnsignedInt_, "initWithUnsignedInt:");
        METALPP_PRIVATE_SEL(initWithLong_, "initWithLong:");
        METALPP_PRIVATE_SEL(initWithUnsignedLong_, "initWithUnsignedLong:");
        METALPP_PRIVATE_SEL(initWithLongLong_, "initWithLongLong:");
        METALPP_PRIVATE_SEL(initWithUnsignedLongLong_, "initWithUnsignedLongLong:");
        METALPP_PRIVATE_SEL(initWithFloat_, "initWithFloat:");
        METALPP_PRIVATE_SEL(initWithDouble_, "initWithDouble:");
        METALPP_PRIVATE_SEL(initWithBool_, "initWithBool:");

        METALPP_PRIVATE_SEL(charValue, "charValue");
        METALPP_PRIVATE_SEL(unsignedCharValue, "unsignedCharValue");
        METALPP_PRIVATE_SEL(shortValue, "shortValue");
        METALPP_PRIVATE_SEL(unsignedShortValue, "unsignedShortValue");
        METALPP_PRIVATE_SEL(intValue, "intValue");
        METALPP_PRIVATE_SEL(unsignedIntValue, "unsignedIntValue");
        METALPP_PRIVATE_SEL(longValue, "longValue");
        METALPP_PRIVATE_SEL(unsignedLongValue, "unsignedLongValue");
        METALPP_PRIVATE_SEL(longLongValue, "longLongValue");
        METALPP_PRIVATE_SEL(unsignedLongLongValue, "unsignedLongLongValue");
        METALPP_PRIVATE_SEL(floatValue, "floatValue");
        METALPP_PRIVATE_SEL(doubleValue, "doubleValue");
        METALPP_PRIVATE_SEL(boolValue, "boolValue");

        using Value::Value;
        using Value::operator=;

        Number() = delete;

        Number(const char value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithChar_), value), adopt}
        {
        }

        Number(const unsigned char value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithUnsignedChar_), value), adopt}
        {
        }

        [[nodiscard]] auto charValue() const noexcept
        {
            return sendMessage<char>(METALPP_SEL(charValue));
        }

        [[nodiscard]] auto unsignedCharValue() const noexcept
        {
            return sendMessage<unsigned char>(METALPP_SEL(unsignedCharValue));
        }
    };
}

#endif
