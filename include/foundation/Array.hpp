#ifndef METALPP_FOUNDATION_ARRAY_HPP
#define METALPP_FOUNDATION_ARRAY_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"

namespace ns
{
    template<class Type>
    class Array: public Object
    {
    public:
        static constexpr bool copying = true;
        
        METALPP_PRIVATE_CLS("NSArray");

        METALPP_PRIVATE_SEL(initWithObjects_, "initWithObjects:");
        METALPP_PRIVATE_SEL(initWithObjects_count_, "initWithObjects:count:");
        METALPP_PRIVATE_SEL(objectAtIndex_, "objectAtIndex:");
        METALPP_PRIVATE_SEL(count, "count");
        
        using Object::Object;
        using Object::operator=;

        Array() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        template<class ...Args>
        Array(const Args&... objects) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithObjects_),
                                         objects.get()...,
                                         nil), adopt}
        {
        }

        [[nodiscard]] auto operator[](const UInteger index) const noexcept
        {
            return objectAtIndex<Type>(index);
        }

        template<class T = Type>
        [[nodiscard]] auto objectAtIndex(const UInteger index) const noexcept
        {
            return T{sendMessage<id>(METALPP_SEL(objectAtIndex_), index)};
        }

        [[nodiscard]] auto count() const noexcept
        {
            return sendMessage<UInteger>(METALPP_SEL(count));
        }
    };
}

#endif
