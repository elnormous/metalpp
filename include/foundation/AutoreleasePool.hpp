#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Selectors.hpp"

namespace ns
{
    class AutoreleasePool final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSAutoreleasePool");
    public:
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage(release(), sel::drain);
        }
    };
}

#endif
