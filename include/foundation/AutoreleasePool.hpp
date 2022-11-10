#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"

namespace ns
{
    class AutoreleasePool final: public ns::Object
    {
        inline static const Class cls = objc_lookUpClass("NSAutoreleasePool");

        inline static const auto allocSel = sel_registerName("alloc");
        inline static const auto initSel = sel_registerName("init");
        inline static const auto drainSel = sel_registerName("drain");

    public:
        AutoreleasePool():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel),
                                         initSel), false}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage<NSUInteger>(*this, drainSel);
        }
    };
}

#endif
