#ifndef METALPP_APPKIT_MENUITEM_HPP
#define METALPP_APPKIT_MENUITEM_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "Event.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Menu;

    class MenuItem final: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSMenuItem");

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
                                         title.get(),
                                         action,
                                         keyEquivalent.get())}
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
            sendMessage(sel::setTitle_, title.get());
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
            sendMessage(sel::setKeyEquivalent_, keyEquivalent.get());
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
