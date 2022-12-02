#ifndef METALPP_APPKIT_APPLICATION_HPP
#define METALPP_APPKIT_APPLICATION_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Menu.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Application final: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSApplication");

        [[nodiscard]] static auto sharedApplication() noexcept
        {
            return Application{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::sharedApplication), sel::retain)};
        }

        Application() = delete;

        [[nodiscard]] auto delegate() const noexcept
        {
            return getRetained<Object>(sel::delegate);
        }

        void setDelegate(const Object& delegate) noexcept
        {
            sendMessage(sel::setDelegate_, delegate.get());
        }

        void activateIgnoringOtherApps(bool flag) noexcept
        {
            sendMessage(sel::activateIgnoringOtherApps_, flag ? YES: NO);
        }

        void run() noexcept
        {
            sendMessage(sel::run);
        }

        [[nodiscard]] auto mainMenu() const noexcept
        {
            return getRetained<ns::Menu>(sel::mainMenu);
        }

        void setMainMenu(const ns::Menu& mainMenu) noexcept
        {
            sendMessage(sel::setMainMenu_, mainMenu.get());
        }

        [[nodiscard]] auto helpMenu() const noexcept API_AVAILABLE(macos(10.6))
        {
            return getRetained<ns::Menu>(sel::helpMenu);
        }

        void setHelpMenu(const ns::Menu& helpMenu) noexcept API_AVAILABLE(macos(10.6))
        {
            sendMessage(sel::setHelpMenu_, helpMenu.get());
        }

        [[nodiscard]] auto windowsMenu() const noexcept
        {
            return getRetained<ns::Menu>(sel::windowsMenu);
        }

        void setWindowsMenu(const ns::Menu& windowsMenu) noexcept
        {
            sendMessage(sel::setWindowsMenu_, windowsMenu.get());
        }

        [[nodiscard]] auto servicesMenu() const noexcept
        {
            return getRetained<ns::Menu>(sel::servicesMenu);
        }

        void setServicesMenu(const ns::Menu& servicesMenu) noexcept
        {
            sendMessage(sel::setServicesMenu_, servicesMenu.get());
        }
    };
}

#endif
