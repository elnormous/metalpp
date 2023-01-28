#ifndef METALPP_APPKIT_APPLICATION_HPP
#define METALPP_APPKIT_APPLICATION_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "Menu.hpp"
#include "RunningApplication.hpp"
#include "Window.hpp"

namespace ns
{
    class Application final: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSApplication");

        METALPP_PRIVATE_SEL(sharedApplication, "sharedApplication");
        METALPP_PRIVATE_SEL(delegate, "delegate");
        METALPP_PRIVATE_SEL(setDelegate_, "setDelegate:");
        METALPP_PRIVATE_SEL(windowWithWindowNumber_, "windowWithWindowNumber:");
        METALPP_PRIVATE_SEL(mainWindow, "mainWindow");
        METALPP_PRIVATE_SEL(keyWindow, "keyWindow");
        METALPP_PRIVATE_SEL(isActive, "isActive");
        METALPP_PRIVATE_SEL(isHidden, "isHidden");
        METALPP_PRIVATE_SEL(isRunning, "isRunning");
        METALPP_PRIVATE_SEL(deactivate, "deactivate");
        METALPP_PRIVATE_SEL(activateIgnoringOtherApps_, "activateIgnoringOtherApps:");
        METALPP_PRIVATE_SEL(finishLaunching, "finishLaunching");
        METALPP_PRIVATE_SEL(run, "run");
        METALPP_PRIVATE_SEL(stop_, "stop:");
        METALPP_PRIVATE_SEL(mainMenu, "mainMenu");
        METALPP_PRIVATE_SEL(setMainMenu_, "setMainMenu:");
        METALPP_PRIVATE_SEL(helpMenu, "helpMenu");
        METALPP_PRIVATE_SEL(setHelpMenu_, "setHelpMenu:");
        METALPP_PRIVATE_SEL(activationPolicy, "activationPolicy");
        METALPP_PRIVATE_SEL(setActivationPolicy_, "setActivationPolicy:");
        METALPP_PRIVATE_SEL(windowsMenu, "windowsMenu");
        METALPP_PRIVATE_SEL(setWindowsMenu_, "setWindowsMenu:");
        METALPP_PRIVATE_SEL(servicesMenu, "servicesMenu");
        METALPP_PRIVATE_SEL(setServicesMenu_, "setServicesMenu:");

        using Object::Object;
        using Object::operator=;

        [[nodiscard]] static auto sharedApplication() noexcept
        {
            return Application{objc::sendMessage<id>(cls, METALPP_SEL(sharedApplication))};
        }

        Application() = delete;

        [[nodiscard]] auto delegate() const noexcept
        {
            return Object{sendMessage<id>(METALPP_SEL(delegate))};
        }

        void setDelegate(const Object& delegate) noexcept
        {
            sendMessage(METALPP_SEL(setDelegate_), delegate.get());
        }

        [[nodiscard]] auto windowWithWindowNumber(const ns::Integer windowNum) const noexcept
        {
            return Window{sendMessage<id>(METALPP_SEL(windowWithWindowNumber_), windowNum)};
        }

        [[nodiscard]] auto mainWindow() const noexcept
        {
            return Window{sendMessage<id>(METALPP_SEL(mainWindow))};
        }

        [[nodiscard]] auto keyWindow() const noexcept
        {
            return Window{sendMessage<id>(METALPP_SEL(mainWindow))};
        }

        [[nodiscard]] auto active() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isActive)) == YES;
        }

        [[nodiscard]] auto hidden() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isHidden)) == YES;
        }

        [[nodiscard]] auto running() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isRunning)) == YES;
        }

        void deactivate() noexcept
        {
            sendMessage(METALPP_SEL(deactivate));
        }

        void activateIgnoringOtherApps(const bool flag) noexcept
        {
            sendMessage(METALPP_SEL(activateIgnoringOtherApps_), flag ? YES: NO);
        }

        void finishLaunching() noexcept
        {
            sendMessage(METALPP_SEL(finishLaunching));
        }

        void run() noexcept
        {
            sendMessage(METALPP_SEL(run));
        }

        void stop(const Object& sender) noexcept
        {
            sendMessage(METALPP_SEL(stop_), sender.get());
        }

        [[nodiscard]] auto mainMenu() const noexcept
        {
            return Menu{sendMessage<id>(METALPP_SEL(mainMenu))};
        }

        void setMainMenu(const Menu& mainMenu) noexcept
        {
            sendMessage(METALPP_SEL(setMainMenu_), mainMenu.get());
        }

        [[nodiscard]] auto helpMenu() const noexcept API_AVAILABLE(macos(10.6))
        {
            return Menu{sendMessage<id>(METALPP_SEL(helpMenu))};
        }

        void setHelpMenu(const Menu& helpMenu) noexcept API_AVAILABLE(macos(10.6))
        {
            sendMessage(METALPP_SEL(setHelpMenu_), helpMenu.get());
        }

        [[nodiscard]] auto activationPolicy() noexcept API_AVAILABLE(macos(10.6))
        {
            return sendMessage<ApplicationActivationPolicy>(METALPP_SEL(activationPolicy));
        }

        auto setActivationPolicy(const ApplicationActivationPolicy activationPolicy) noexcept API_AVAILABLE(macos(10.6))
        {
            return sendMessage<BOOL>(METALPP_SEL(setActivationPolicy_), activationPolicy);
        }

        [[nodiscard]] auto windowsMenu() const noexcept
        {
            return Menu{sendMessage<id>(METALPP_SEL(windowsMenu))};
        }

        void setWindowsMenu(const Menu& windowsMenu) noexcept
        {
            sendMessage(METALPP_SEL(setWindowsMenu_), windowsMenu.get());
        }

        [[nodiscard]] auto servicesMenu() const noexcept
        {
            return Menu{sendMessage<id>(METALPP_SEL(servicesMenu))};
        }

        void setServicesMenu(const Menu& servicesMenu) noexcept
        {
            sendMessage(METALPP_SEL(setServicesMenu_), servicesMenu.get());
        }
    };

    enum class ApplicationTerminateReply: ns::UInteger
    {
        TerminateCancel = 0,
        TerminateNow = 1,
        TerminateLater = 2
    };

    enum class ApplicationPrintReply: ns::UInteger
    {
        PrintingCancelled = 0,
        PrintingSuccess = 1,
        PrintingFailure = 3,
        PrintingReplyLater = 2
    };
}

#endif
