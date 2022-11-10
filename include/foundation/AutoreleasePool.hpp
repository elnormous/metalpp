#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"

namespace ns
{
    inline namespace detail
    {
        inline const Class autoreleasePoolClass = objc_lookUpClass("NSAutoreleasePool");
    }

    class AutoreleasePool final: public ns::Object
    {
    public:
        AutoreleasePool():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(autoreleasePoolClass, ns::allocSel),
                                         ns::initSel), false}
        {            
        }
    };
}

#endif
