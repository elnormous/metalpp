#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"

namespace ns
{
    class AutoreleasePool final: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSAutoreleasePool");

        METALPP_PRIVATE_SEL(drain, "drain");
        
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage(release(), METALPP_SEL(drain));
        }
    };
}

#endif
