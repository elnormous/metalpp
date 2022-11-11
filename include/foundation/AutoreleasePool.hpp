#ifndef METALPP_FOUNDATION_AUTORELEASEPOOL_HPP
#define METALPP_FOUNDATION_AUTORELEASEPOOL_HPP

#include "../objc/Classes.hpp"
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"

namespace ns
{
    class AutoreleasePool final: public ns::Object
    {
    public:
        AutoreleasePool() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::autoreleasePoolClass, objc::sel::alloc), objc::sel::init)}
        {            
        }

        void drain() noexcept
        {
            objc::sendMessage(*this, objc::sel::drain);
        }
    };
}

#endif
