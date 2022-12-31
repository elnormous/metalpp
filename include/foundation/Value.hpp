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

        Number(const short value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithShort_), value), adopt}
        {
        }

        Number(const unsigned short value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithUnsignedShort_), value), adopt}
        {
        }

        Number(const int value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithInt_), value), adopt}
        {
        }

        Number(const unsigned int value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithUnsignedInt_), value), adopt}
        {
        }

        Number(const long value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithLong_), value), adopt}
        {
        }

        Number(const unsigned long value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithUnsignedLong_), value), adopt}
        {
        }

        Number(const long long value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithLongLong_), value), adopt}
        {
        }

        Number(const unsigned long long value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithUnsignedLongLong_), value), adopt}
        {
        }

        Number(const float value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithFloat_), value), adopt}
        {
        }

        Number(const double value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithDouble_), value), adopt}
        {
        }

        Number(const bool value):
            Value{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithBool_), value ? YES : NO), adopt}
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

        [[nodiscard]] auto shortValue() const noexcept
        {
            return sendMessage<short>(METALPP_SEL(shortValue));
        }

        [[nodiscard]] auto unsignedShortValue() const noexcept
        {
            return sendMessage<unsigned short>(METALPP_SEL(unsignedShortValue));
        }

        [[nodiscard]] auto intValue() const noexcept
        {
            return sendMessage<int>(METALPP_SEL(intValue));
        }

        [[nodiscard]] auto unsignedIntValue() const noexcept
        {
            return sendMessage<unsigned int>(METALPP_SEL(unsignedIntValue));
        }

        [[nodiscard]] auto longValue() const noexcept
        {
            return sendMessage<long>(METALPP_SEL(longValue));
        }

        [[nodiscard]] auto unsignedLongValue() const noexcept
        {
            return sendMessage<unsigned long>(METALPP_SEL(unsignedLongValue));
        }

        [[nodiscard]] auto longLongValue() const noexcept
        {
            return sendMessage<long long>(METALPP_SEL(longLongValue));
        }

        [[nodiscard]] auto unsignedLongLongValue() const noexcept
        {
            return sendMessage<unsigned long long>(METALPP_SEL(unsignedLongLongValue));
        }

        [[nodiscard]] auto floatValue() const noexcept
        {
            return sendMessage<float>(METALPP_SEL(floatValue));
        }

        [[nodiscard]] auto doubleValue() const noexcept
        {
            return sendMessage<double>(METALPP_SEL(doubleValue));
        }

        [[nodiscard]] auto boolValue() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(boolValue)) == YES;
        }
    };
}

#endif
