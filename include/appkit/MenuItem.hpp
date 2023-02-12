#ifndef METALPP_APPKIT_MENUITEM_HPP
#define METALPP_APPKIT_MENUITEM_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Object.hpp"
#include "Event.hpp"

namespace ns
{
    class Menu;

    class MenuItem final: public Object, public Copying
    {
    public:
        METALPP_PRIVATE_CLS("NSMenuItem");

        METALPP_PRIVATE_SEL(separatorItem, "separatorItem");
        METALPP_PRIVATE_SEL(initWithTitle_action_keyEquivalent_, "initWithTitle:action:keyEquivalent:");
        METALPP_PRIVATE_SEL(submenu, "submenu");
        METALPP_PRIVATE_SEL(setSubmenu_, "setSubmenu:");
        METALPP_PRIVATE_SEL(title, "title");
        METALPP_PRIVATE_SEL(setTitle_, "setTitle:");
        METALPP_PRIVATE_SEL(isSeparatorItem, "isSeparatorItem");
        METALPP_PRIVATE_SEL(keyEquivalent, "keyEquivalent");
        METALPP_PRIVATE_SEL(setKeyEquivalent_, "setKeyEquivalent:");
        METALPP_PRIVATE_SEL(keyEquivalentModifierMask, "keyEquivalentModifierMask");
        METALPP_PRIVATE_SEL(setKeyEquivalentModifierMask_, "setKeyEquivalentModifierMask:");
        METALPP_PRIVATE_SEL(tag, "tag");
        METALPP_PRIVATE_SEL(setTag_, "setTag:");

        using Object::Object;
        using Object::operator=;

        [[nodiscard]] static auto separatorItem() noexcept
        {
            return MenuItem{objc::sendMessage<id>(cls, METALPP_SEL(separatorItem))};
        }

        MenuItem() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        MenuItem(const String& title, const SEL action, const String& keyEquivalent) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithTitle_action_keyEquivalent_),
                                         title.get(),
                                         action,
                                         keyEquivalent.get()), adopt}
        {
        }

        [[nodiscard]] inline Menu submenu() const noexcept;
        inline void setSubmenu(const Menu& submenu) noexcept;

        [[nodiscard]] auto title() const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(title))};
        }

        void setTitle(const String& title) noexcept
        {
            sendMessage(METALPP_SEL(setTitle_), title.get());
        }

        [[nodiscard]] auto isSeparatorItem() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isSeparatorItem)) == YES;
        }

        [[nodiscard]] auto keyEquivalent() const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(keyEquivalent))};
        }

        void setKeyEquivalent(const String& keyEquivalent) noexcept
        {
            sendMessage(METALPP_SEL(setKeyEquivalent_), keyEquivalent.get());
        }

        [[nodiscard]] auto keyEquivalentModifierMask() const noexcept
        {
            return sendMessage<EventModifierFlags>(METALPP_SEL(keyEquivalentModifierMask));
        }

        void setKeyEquivalentModifierMask(const EventModifierFlags keyEquivalentModifierMask) noexcept
        {
            sendMessage(METALPP_SEL(setKeyEquivalentModifierMask_), keyEquivalentModifierMask);
        }

        [[nodiscard]] auto tag() const noexcept
        {
            return sendMessage<NSInteger>(METALPP_SEL(tag));
        }

        void setTag(const NSInteger tag) noexcept
        {
            sendMessage(METALPP_SEL(setTag_), tag);
        }
    };
}

#endif
