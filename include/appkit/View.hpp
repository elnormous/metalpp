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

        METALPP_PRIVATE_SEL(initWithFrame_, "initWithFrame:");

        using Object::Object;

        View() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {
        }

        View(const ns::Rect& frameRect) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithFrame_), frameRect)}
        {
        }
    };
}

#endif
