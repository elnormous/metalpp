#ifndef METALPP_FOUNDATION_ARRAY_HPP
#define METALPP_FOUNDATION_ARRAY_HPP

#include <cstdint>
#include <objc/NSObjCRuntime.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class Type>
    class Array final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("NSArray");
    public:
        Array() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        Array(const id p) noexcept: Object{p} {}

        template <class ...Args>
        Array(const Args&... objects) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::initWithObjects_, static_cast<id>(objects)..., nil)}
        {
        }

        [[nodiscard]] Type operator[](const std::size_t index) const noexcept
        {
            return objectAtIndex(static_cast<NSUInteger>(index));
        }

        [[nodiscard]] Type objectAtIndex(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndex_,
                                                    index);
            return Type{objc::sendMessage<id>(object, ns::sel::retain)};
        }

        [[nodiscard]] std::size_t count() const noexcept
        {
            const auto count = objc::sendMessage<NSUInteger>(*this, sel::count);
            return static_cast<std::size_t>(count);
        }
    };
}

#endif
