#ifndef METALPP_APPKIT_VIEW_HPP
#define METALPP_APPKIT_VIEW_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"

namespace ns
{
    class View: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSView");

        using Object::Object;

        View() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {
        }
    };
}

#endif
