#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"

namespace ns
{
    class AutoreleasePool final: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSAutoreleasePool");

        METALPP_PRIVATE_SEL(drain, "drain");

        using Object::Object;
        using Object::operator=;
        
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        void drain() noexcept
        {
            objc::sendMessage(release(), METALPP_SEL(drain));
        }
    };
}

#endif
