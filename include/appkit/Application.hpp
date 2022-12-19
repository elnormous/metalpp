#ifndef METALPP_APPKIT_APPLICATION_HPP
#define METALPP_APPKIT_APPLICATION_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "Menu.hpp"

namespace ns
{
    class Application final: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSApplication");

        METALPP_PRIVATE_SEL(sharedApplication, "sharedApplication");
        METALPP_PRIVATE_SEL(delegate, "delegate");
        METALPP_PRIVATE_SEL(setDelegate_, "setDelegate:");
        METALPP_PRIVATE_SEL(activateIgnoringOtherApps_, "activateIgnoringOtherApps:");
        METALPP_PRIVATE_SEL(run, "run");
        METALPP_PRIVATE_SEL(mainMenu, "mainMenu");
        METALPP_PRIVATE_SEL(setMainMenu_, "setMainMenu:");
        METALPP_PRIVATE_SEL(helpMenu, "helpMenu");
        METALPP_PRIVATE_SEL(setHelpMenu_, "setHelpMenu:");
        METALPP_PRIVATE_SEL(windowsMenu, "windowsMenu");
        METALPP_PRIVATE_SEL(setWindowsMenu_, "setWindowsMenu:");
        METALPP_PRIVATE_SEL(servicesMenu, "servicesMenu");
        METALPP_PRIVATE_SEL(setServicesMenu_, "setServicesMenu:");

        using Object::Object;

        [[nodiscard]] static auto sharedApplication() noexcept
        {
            return Application{objc::sendMessage<id>(cls, METALPP_SEL(sharedApplication))};
        }

        Application() = delete;

        [[nodiscard]] auto delegate() const noexcept
        {
            return getRetained<Object>(METALPP_SEL(delegate));
        }

        void setDelegate(const Object& delegate) noexcept
        {
            sendMessage(METALPP_SEL(setDelegate_), delegate.get());
        }

        void activateIgnoringOtherApps(const bool flag) noexcept
        {
            sendMessage(METALPP_SEL(activateIgnoringOtherApps_), flag ? YES: NO);
        }

        void run() noexcept
        {
            sendMessage(METALPP_SEL(run));
        }

        [[nodiscard]] auto mainMenu() const noexcept
        {
            return getRetained<Menu>(METALPP_SEL(mainMenu));
        }

        void setMainMenu(const Menu& mainMenu) noexcept
        {
            sendMessage(METALPP_SEL(setMainMenu_), mainMenu.get());
        }

        [[nodiscard]] auto helpMenu() const noexcept API_AVAILABLE(macos(10.6))
        {
            return getRetained<Menu>(METALPP_SEL(helpMenu));
        }

        void setHelpMenu(const Menu& helpMenu) noexcept API_AVAILABLE(macos(10.6))
        {
            sendMessage(METALPP_SEL(setHelpMenu_), helpMenu.get());
        }

        [[nodiscard]] auto windowsMenu() const noexcept
        {
            return getRetained<Menu>(METALPP_SEL(windowsMenu));
        }

        void setWindowsMenu(const Menu& windowsMenu) noexcept
        {
            sendMessage(METALPP_SEL(setWindowsMenu_), windowsMenu.get());
        }

        [[nodiscard]] auto servicesMenu() const noexcept
        {
            return getRetained<Menu>(METALPP_SEL(servicesMenu));
        }

        void setServicesMenu(const Menu& servicesMenu) noexcept
        {
            sendMessage(METALPP_SEL(setServicesMenu_), servicesMenu.get());
        }
    };
}

#endif
