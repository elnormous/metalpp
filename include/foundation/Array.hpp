#ifndef METALPP_FOUNDATION_ARRAY_HPP
#define METALPP_FOUNDATION_ARRAY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class Type>
    class Array final: public ns::Object
    {
    public:
        Array() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::array, ns::sel::alloc), ns::sel::init)}
        {
        }

        Array(const id p) noexcept: Object{p} {}

        template <class ...Args>
        Array(const Args&... objects) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::array, ns::sel::alloc), ns::sel::initWithObjects_, static_cast<id>(objects)..., nil)}
        {
        }

        Type operator[](const std::size_t index) const noexcept
        {
            return objectAtIndexedSubscript(static_cast<NSUInteger>(index));
        }

        Type objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndexedSubscript_,
                                                    index);
            return Type{objc::sendMessage<id>(object, ns::sel::retain)};
        }
    };
}

#endif
