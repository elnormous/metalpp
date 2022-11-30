#ifndef METALPP_APPKIT_MENUITEM_HPP
#define METALPP_APPKIT_MENUITEM_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"

namespace ns
{
    class Menu;

    class MenuItem final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSMenuItem");
    public:
        using Object::Object;

        static auto separatorItem() noexcept
        {
            return MenuItem{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::separatorItem), sel::retain)};
        }

        MenuItem():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        MenuItem(const ns::String& title, const SEL action, const ns::String& keyEquivalent):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithTitle_action_keyEquivalent_,
                                         static_cast<id>(title),
                                         action,
                                         static_cast<id>(keyEquivalent))}
        {
        }

        inline Menu submenu() const noexcept;
        inline void setSubmenu(const Menu& submenu) noexcept;
    };
}

#endif
