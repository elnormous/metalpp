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
        using Object::Object;

        Array() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

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
            return objectAtIndex<Type>(index);
        }

        template<class T = Type>
        [[nodiscard]] auto objectAtIndex(const UInteger index) const noexcept
        {
            return getRetained<T>(sel::objectAtIndex_, index);
        }

        [[nodiscard]] auto count() const noexcept
        {
            return sendMessage<UInteger>(sel::count);
        }
    };
}

#endif
