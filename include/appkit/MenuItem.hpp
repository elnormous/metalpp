#ifndef METALPP_APPKIT_MENUITEM_HPP
#define METALPP_APPKIT_MENUITEM_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "Event.hpp"

namespace ns
{
    class Menu;

    class MenuItem final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSMenuItem");
    public:
        using Object::Object;

        [[nodiscard]] static auto separatorItem() noexcept
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

        [[nodiscard]] inline Menu submenu() const noexcept;
        inline void setSubmenu(const Menu& submenu) noexcept;

        [[nodiscard]] auto title() const noexcept
        {
            return getRetained<String>(sel::title);
        }

        void setTitle(const String& title) noexcept
        {
            sendMessage(sel::setTitle_, static_cast<id>(title));
        }

        [[nodiscard]] auto isSeparatorItem() const noexcept
        {
            return sendMessage<BOOL>(sel::isSeparatorItem) == YES;
        }

        [[nodiscard]] auto keyEquivalent() const noexcept
        {
            return getRetained<String>(sel::keyEquivalent);
        }

        void setKeyEquivalent(const String& keyEquivalent) noexcept
        {
            sendMessage(sel::setKeyEquivalent_, static_cast<id>(keyEquivalent));
        }

        [[nodiscard]] auto keyEquivalentModifierMask() const noexcept
        {
            return sendMessage<ns::EventModifierFlags>(sel::keyEquivalentModifierMask);
        }

        void setKeyEquivalentModifierMask(const ns::EventModifierFlags keyEquivalentModifierMask) noexcept
        {
            sendMessage(sel::setKeyEquivalentModifierMask_, keyEquivalentModifierMask);
        }
    };
}

#endif
