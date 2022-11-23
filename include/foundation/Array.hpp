#ifndef METALPP_FOUNDATION_ARRAY_HPP
#define METALPP_FOUNDATION_ARRAY_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class Type>
    class Array: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSArray");
    public:
        Array() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        Array(const id p) noexcept: Object{p} {}

        template <class ...Args>
        Array(const Args&... objects) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithObjects_,
                                         static_cast<id>(objects)...,
                                         nil)}
        {
        }

        [[nodiscard]] auto operator[](const UInteger index) const noexcept
        {
            return objectAtIndex(index);
        }

        [[nodiscard]] auto objectAtIndex(const UInteger index) const noexcept
        {
            return getRetained<Type>(sel::objectAtIndex_, index);
        }

        [[nodiscard]] auto count() const noexcept
        {
            return sendMessage<UInteger>(sel::count);
        }
    };
}

#endif
