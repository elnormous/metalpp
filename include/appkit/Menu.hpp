#ifndef METALPP_APPKIT_MENU_HPP
#define METALPP_APPKIT_MENU_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/String.hpp"
#include "MenuItem.hpp"

namespace ns
{
    class Menu final: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSMenu");

        METALPP_PRIVATE_SEL(initWithTitle_, "initWithTitle:");
        METALPP_PRIVATE_SEL(insertItem_atIndex_, "insertItem:atIndex:");
        METALPP_PRIVATE_SEL(addItem_, "addItem:");
        METALPP_PRIVATE_SEL(insertItemWithTitle_action_keyEquivalent_atIndex_, "insertItemWithTitle:action:keyEquivalent:atIndex:");
        METALPP_PRIVATE_SEL(addItemWithTitle_action_keyEquivalent_, "addItemWithTitle:action:keyEquivalent:");
        
        using Object::Object;

        Menu():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {
        }

        Menu(const ns::String& title):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithTitle_),
                                         title.get())}
        {
        }

        void insertItem(const MenuItem& item, ns::Integer index) noexcept
        {
            sendMessage(METALPP_SEL(insertItem_atIndex_), item.get(), index);
        }

        void addItem(const MenuItem& item) noexcept
        {
            sendMessage(METALPP_SEL(addItem_), item.get());
        }

        auto insertItem(const ns::String& title, const SEL action, const ns::String& keyEquivalent, ns::Integer index) noexcept
        {
            return getRetained<MenuItem>(METALPP_SEL(insertItemWithTitle_action_keyEquivalent_atIndex_),
                                         title.get(),
                                         action,
                                         keyEquivalent.get(),
                                         index);
        }

        auto addItem(const ns::String& title, const SEL action, const ns::String& keyEquivalent) noexcept
        {
            return getRetained<MenuItem>(METALPP_SEL(addItemWithTitle_action_keyEquivalent_),
                                         title.get(),
                                         action,
                                         keyEquivalent.get());
        }
    };

    [[nodiscard]] inline Menu MenuItem::submenu() const noexcept
    {
        return getRetained<Menu>(METALPP_SEL(submenu));
    }

    inline void MenuItem::setSubmenu(const Menu& submenu) noexcept
    {
        sendMessage(METALPP_SEL(setSubmenu_), submenu.get());
    }
}

#endif
