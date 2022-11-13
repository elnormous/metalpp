#ifndef METALPP_FOUNDATION_ARRAY_HPP
#define METALPP_FOUNDATION_ARRAY_HPP

#include <initializer_list>
#include <type_traits>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class T>
    class Array final: public ns::Object
    {
    public:
        Array() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::array, ns::sel::alloc), ns::sel::init)}
        {
        }

        //typename std::enable_if<std::is_same_v<Args, T>, Args>::type

        template <class... Args>
        Array(const Args&... objects) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::array, ns::sel::alloc), ns::sel::initWithObjects_, static_cast<id>(objects)..., nil)}
        {
        }

        T operator[](const std::size_t index) const noexcept
        {
            return objectAtIndexedSubscript(static_cast<NSUInteger>(index));
        }

        T objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndexedSubscript_,
                                                    index);
            return T{objc::sendMessage<id>(object, ns::sel::retain)};
        }
    };
}

#endif
