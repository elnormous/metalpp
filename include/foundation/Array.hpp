#ifndef METALPP_FOUNDATION_ARRAY_HPP
#define METALPP_FOUNDATION_ARRAY_HPP

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
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        Array(const id p) noexcept: Object{p} {}

        template <class ...Args>
        Array(const Args&... objects) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::initWithObjects_, static_cast<id>(objects)..., nil)}
        {
        }

        [[nodiscard]] Type operator[](const NSUInteger index) const noexcept
        {
            return objectAtIndex(index);
        }

        [[nodiscard]] Type objectAtIndex(const NSUInteger index) const noexcept
        {
            return getRetained<Type>(ns::sel::objectAtIndex_, index);
        }

        [[nodiscard]] NSUInteger count() const noexcept
        {
            return sendMessage<NSUInteger>(sel::count);
        }
    };
}

#endif
