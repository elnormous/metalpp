#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"

namespace ns
{
    class AutoreleasePool final: public ns::Object
    {
        inline static const auto cls = objc_lookUpClass("NSAutoreleasePool");

        inline static const auto drainSel = sel_registerName("drain");

    public:
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel), initSel)}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage<NSUInteger>(*this, drainSel);
        }
    };
}

#endif
