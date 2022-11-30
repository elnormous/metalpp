#ifndef METALPP_APPKIT_MENU_HPP
#define METALPP_APPKIT_MENU_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"
#include "MenuItem.hpp"

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

        Menu(const ns::String& title):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithTitle_,
                                         static_cast<id>(title))}
        {
        }

        void insertItem(const MenuItem& item, ns::Integer index) noexcept
        {
            sendMessage(sel::insertItem_atIndex_, static_cast<id>(item), index);
        }

        void addItem(const MenuItem& item) noexcept
        {
            sendMessage(sel::addItem_, static_cast<id>(item));
        }

        auto insertItem(const ns::String& title, const SEL action, const ns::String& keyEquivalent, ns::Integer index) noexcept
        {
            return getRetained<MenuItem>(sel::insertItemWithTitle_action_keyEquivalent_atIndex_,
                                         static_cast<id>(title),
                                         action,
                                         static_cast<id>(keyEquivalent),
                                         index);
        }

        auto addItem(const ns::String& title, const SEL action, const ns::String& keyEquivalent) noexcept
        {
            return getRetained<MenuItem>(sel::addItemWithTitle_action_keyEquivalent_,
                                         static_cast<id>(title),
                                         action,
                                         static_cast<id>(keyEquivalent));
        }
    };

    inline Menu MenuItem::submenu() const noexcept
    {
        return getRetained<Menu>(sel::submenu);
    }

    inline void MenuItem::setSubmenu(const Menu& submenu) noexcept
    {
        sendMessage(sel::setSubmenu_, static_cast<id>(submenu));
    }
}

#endif
