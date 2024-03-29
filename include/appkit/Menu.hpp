#ifndef METALPP_APPKIT_MENU_HPP
#define METALPP_APPKIT_MENU_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Object.hpp"
#include "../foundation/String.hpp"
#include "MenuItem.hpp"

namespace ns
{
    class Menu final: public Object, public Copying
    {
    public:
        METALPP_PRIVATE_CLS("NSMenu");

        METALPP_PRIVATE_SEL(initWithTitle_, "initWithTitle:");
        METALPP_PRIVATE_SEL(insertItem_atIndex_, "insertItem:atIndex:");
        METALPP_PRIVATE_SEL(addItem_, "addItem:");
        METALPP_PRIVATE_SEL(insertItemWithTitle_action_keyEquivalent_atIndex_, "insertItemWithTitle:action:keyEquivalent:atIndex:");
        METALPP_PRIVATE_SEL(addItemWithTitle_action_keyEquivalent_, "addItemWithTitle:action:keyEquivalent:");
        METALPP_PRIVATE_SEL(itemWithTitle_, "itemWithTitle:");
        METALPP_PRIVATE_SEL(itemWithTag_, "itemWithTag:");
        
        using Object::Object;
        using Object::operator=;

        Menu() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        Menu(const String& title):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithTitle_),
                                         title.get()), adopt}
        {
        }

        void insertItem(const MenuItem& item, Integer index) noexcept
        {
            sendMessage(METALPP_SEL(insertItem_atIndex_), item.get(), index);
        }

        void addItem(const MenuItem& item) noexcept
        {
            sendMessage(METALPP_SEL(addItem_), item.get());
        }

        auto insertItem(const String& title, const SEL action, const String& keyEquivalent, Integer index) noexcept
        {
            return MenuItem{sendMessage<id>(METALPP_SEL(insertItemWithTitle_action_keyEquivalent_atIndex_),
                                            title.get(),
                                            action,
                                            keyEquivalent.get(),
                                            index)};
        }

        auto addItem(const String& title, const SEL action, const String& keyEquivalent) noexcept
        {
            return MenuItem{sendMessage<id>(METALPP_SEL(addItemWithTitle_action_keyEquivalent_),
                                            title.get(),
                                            action,
                                            keyEquivalent.get())};
        }

        auto itemWithTitle(const String& title) noexcept
        {
            return MenuItem{sendMessage<id>(METALPP_SEL(itemWithTitle_), title.get())};
        }

        auto itemWithTag(const NSInteger tag) noexcept
        {
            return MenuItem{sendMessage<id>(METALPP_SEL(itemWithTag_), tag)};
        }
    };

    [[nodiscard]] inline Menu MenuItem::submenu() const noexcept
    {
        return Menu{sendMessage<id>(METALPP_SEL(submenu))};
    }

    inline void MenuItem::setSubmenu(const Menu& submenu) noexcept
    {
        sendMessage(METALPP_SEL(setSubmenu_), submenu.get());
    }
}

#endif
