#ifndef METALPP_APPKIT_MENU_HPP
#define METALPP_APPKIT_MENU_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"

namespace ns
{
    class Menu final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSMenu");
    public:
        using Object::Object;

        Menu():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }
    };
}

#endif
