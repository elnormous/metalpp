#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace ns
{
    class AutoreleasePool final: public ns::Object
    {
    public:
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::autoreleasePool, ns::sel::alloc), ns::sel::init)}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage(release(), sel::drain);
        }
    };
}

#endif
