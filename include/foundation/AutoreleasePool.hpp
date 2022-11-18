#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Selectors.hpp"

namespace ns
{
    class AutoreleasePool final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("NSAutoreleasePool");
    public:
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage(release(), sel::drain);
        }
    };
}

#endif
