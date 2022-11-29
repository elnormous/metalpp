#ifndef METALPP_APPKIT_MENUITEM_HPP
#define METALPP_APPKIT_MENUITEM_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"

namespace ns
{
    class MenuItem final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSMenuItem");
    public:
        using Object::Object;

        MenuItem():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }
    };
}

#endif
