#ifndef METALPP_APPKIT_VIEW_HPP
#define METALPP_APPKIT_VIEW_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"

namespace ns
{
    class View: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSView");

        using Object::Object;

        View() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }
    };
}

#endif
