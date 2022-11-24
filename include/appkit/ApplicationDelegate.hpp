#ifndef METALPP_APPKIT_APPLICATIONDELEGATE_HPP
#define METALPP_APPKIT_APPLICATIONDELEGATE_HPP

#include "../objc/Object.hpp"
#include "Selectors.hpp"

namespace ns
{
    class ApplicationDelegate final: public Object
    {
        static Class createClass()
        {
            const auto result = objc_allocateClassPair(Object::cls, "ApplicationDelegate", 0);

            return result;
        }

        static inline const auto cls = createClass();
    public:
        ApplicationDelegate() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }
    };
}

#endif
