#ifndef METALPP_APPKIT_WINDOW_HPP
#define METALPP_APPKIT_WINDOW_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Geometry.hpp"
#include "../foundation/String.hpp"
#include "Graphics.hpp"
#include "Screen.hpp"
#include "View.hpp"

namespace ns
{
    enum class WindowStyleMask: ns::UInteger
    {
        Borderless = 0,
        Titled = 1 << 0,
        Closable = 1 << 1,
        Miniaturizable = 1 << 2,
        Resizable    = 1 << 3,
        TexturedBackground API_DEPRECATED("Textured window style should no longer be used", macos(10.2, 11.0)) = 1 << 8,
        UnifiedTitleAndToolbar = 1 << 12,
        FullScreen API_AVAILABLE(macos(10.7)) = 1 << 14,
        FullSizeContentView API_AVAILABLE(macos(10.10)) = 1 << 15,
        UtilityWindow = 1 << 4,
        DocModalWindow = 1 << 6,
        NonactivatingPanel = 1 << 7,
        HUDWindow API_AVAILABLE(macos(10.6)) = 1 << 13
    };

    inline constexpr WindowStyleMask operator&(const WindowStyleMask a, const WindowStyleMask b) noexcept
    {
        return static_cast<WindowStyleMask>(static_cast<std::underlying_type_t<WindowStyleMask>>(a) & static_cast<std::underlying_type_t<WindowStyleMask>>(b));
    }
    inline constexpr WindowStyleMask operator|(const WindowStyleMask a, const WindowStyleMask b) noexcept
    {
        return static_cast<WindowStyleMask>(static_cast<std::underlying_type_t<WindowStyleMask>>(a) | static_cast<std::underlying_type_t<WindowStyleMask>>(b));
    }
    inline constexpr WindowStyleMask operator^(const WindowStyleMask a, const WindowStyleMask b) noexcept
    {
        return static_cast<WindowStyleMask>(static_cast<std::underlying_type_t<WindowStyleMask>>(a) ^ static_cast<std::underlying_type_t<WindowStyleMask>>(b));
    }
    inline constexpr WindowStyleMask operator~(const WindowStyleMask a) noexcept
    {
        return static_cast<WindowStyleMask>(~static_cast<std::underlying_type_t<WindowStyleMask>>(a));
    }
    inline constexpr WindowStyleMask& operator&=(WindowStyleMask& a, const WindowStyleMask b) noexcept
    {
        return a = static_cast<WindowStyleMask>(static_cast<std::underlying_type_t<WindowStyleMask>>(a) & static_cast<std::underlying_type_t<WindowStyleMask>>(b));
    }
    inline constexpr WindowStyleMask& operator|=(WindowStyleMask& a, const WindowStyleMask b) noexcept
    {
        return a = static_cast<WindowStyleMask>(static_cast<std::underlying_type_t<WindowStyleMask>>(a) | static_cast<std::underlying_type_t<WindowStyleMask>>(b));
    }
    inline constexpr WindowStyleMask& operator^=(WindowStyleMask& a, const WindowStyleMask b) noexcept
    {
        return a = static_cast<WindowStyleMask>(static_cast<std::underlying_type_t<WindowStyleMask>>(a) ^ static_cast<std::underlying_type_t<WindowStyleMask>>(b));
    }

    enum class WindowTabbingMode: ns::Integer
    {
        Automatic,
        Preferred,
        Disallowed
    }  API_AVAILABLE(macos(10.12));

    enum class WindowCollectionBehavior: ns::UInteger
    {
        Default = 0,
        CanJoinAllSpaces = 1 << 0,
        MoveToActiveSpace = 1 << 1,

        Managed API_AVAILABLE(macos(10.6)) = 1 << 2,
        Transient API_AVAILABLE(macos(10.6)) = 1 << 3,
        Stationary API_AVAILABLE(macos(10.6)) = 1 << 4,

        ParticipatesInCycle API_AVAILABLE(macos(10.6)) = 1 << 5,
        IgnoresCycle API_AVAILABLE(macos(10.6)) = 1 << 6,

        FullScreenPrimary API_AVAILABLE(macos(10.7)) = 1 << 7,
        FullScreenAuxiliary API_AVAILABLE(macos(10.7)) = 1 << 8,
        FullScreenNone API_AVAILABLE(macos(10.7)) = 1 << 9,

        FullScreenAllowsTiling API_AVAILABLE(macos(10.11)) = 1 << 11,
        FullScreenDisallowsTiling API_AVAILABLE(macos(10.11)) = 1 << 12,

        Primary API_AVAILABLE(macos(13.0)) = 1 << 16,
        Auxiliary API_AVAILABLE(macos(13.0)) = 1 << 17,
        CanJoinAllApplications API_AVAILABLE(macos(13.0)) = 1 << 18,
    } API_AVAILABLE(macos(10.5));

    class Window final: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSWindow");

        METALPP_PRIVATE_SEL(initWithContentRect_styleMask_backing_defer_, "initWithContentRect:styleMask:backing:defer:");
        METALPP_PRIVATE_SEL(initWithContentRect_styleMask_backing_defer_screen_, "initWithContentRect:styleMask:backing:defer:screen:");
        METALPP_PRIVATE_SEL(title, "title");
        METALPP_PRIVATE_SEL(setTitle_, "setTitle:");
        METALPP_PRIVATE_SEL(contentView, "contentView");
        METALPP_PRIVATE_SEL(setContentView_, "setContentView:");
        METALPP_PRIVATE_SEL(delegate, "delegate");
        METALPP_PRIVATE_SEL(setDelegate_, "setDelegate:");
        METALPP_PRIVATE_SEL(isReleasedWhenClosed, "isReleasedWhenClosed");
        METALPP_PRIVATE_SEL(setReleasedWhenClosed, "setReleasedWhenClosed:");
        METALPP_PRIVATE_SEL(close, "close");
        METALPP_PRIVATE_SEL(center, "center");
        METALPP_PRIVATE_SEL(makeKeyAndOrderFront_, "makeKeyAndOrderFront:");
        METALPP_PRIVATE_SEL(orderFront_, "orderFront:");
        METALPP_PRIVATE_SEL(orderBack_, "orderBack:");
        METALPP_PRIVATE_SEL(orderOut_, "orderOut:");
        METALPP_PRIVATE_SEL(orderWindow_relativeTo_, "orderWindow:relativeTo:");
        METALPP_PRIVATE_SEL(orderFrontRegardless, "orderFrontRegardless");
        METALPP_PRIVATE_SEL(collectionBehavior, "collectionBehavior");
        METALPP_PRIVATE_SEL(setCollectionBehavior_, "setCollectionBehavior:");
        METALPP_PRIVATE_SEL(tabbingMode, "tabbingMode");
        METALPP_PRIVATE_SEL(setTabbingMode_, "setTabbingMode:");
        METALPP_PRIVATE_SEL(acceptsMouseMovedEvents, "acceptsMouseMovedEvents");
        METALPP_PRIVATE_SEL(setAcceptsMouseMovedEvents_, "setAcceptsMouseMovedEvents:");
        METALPP_PRIVATE_SEL(ignoresMouseEvents, "ignoresMouseEvents");
        METALPP_PRIVATE_SEL(setIgnoresMouseEvents_, "setIgnoresMouseEvents:");
        
        using Object::Object;
        Window() = delete;

        Window(const Rect contentRect, const WindowStyleMask style, const BackingStoreType backingStoreType, bool defer) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithContentRect_styleMask_backing_defer_),
                                         contentRect,
                                         style,
                                         backingStoreType,
                                         defer ? YES : NO)}
        {
            sendMessage(METALPP_SEL(setReleasedWhenClosed), NO);
        }

        Window(const Rect contentRect, const WindowStyleMask style, const BackingStoreType backingStoreType, bool defer, const Screen& screen) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithContentRect_styleMask_backing_defer_screen_),
                                         contentRect,
                                         style,
                                         backingStoreType,
                                         defer ? YES : NO,
                                         screen.get())}
        {
            sendMessage(METALPP_SEL(setReleasedWhenClosed), NO);
        }

        [[nodiscard]] auto title() const noexcept
        {
            return getRetained<ns::String>(METALPP_SEL(title));
        }

        void setTitle(const ns::String& title) noexcept
        {
            sendMessage(METALPP_SEL(setTitle_), title.get());
        }

        [[nodiscard]] auto contentView() const noexcept
        {
            return getRetained<View>(METALPP_SEL(contentView));
        }

        void setContentView(const View& contentView) noexcept
        {
            sendMessage(METALPP_SEL(setContentView_), contentView.get());
        }

        [[nodiscard]] auto delegate() const noexcept
        {
            return getRetained<Object>(METALPP_SEL(delegate));
        }

        void setDelegate(const Object& delegate) noexcept
        {
            sendMessage(METALPP_SEL(setDelegate_), delegate.get());
        }

        [[nodiscard]] auto releasedWhenClosed() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isReleasedWhenClosed)) == YES;
        }

        void close() const noexcept { sendMessage(METALPP_SEL(close)); }
        void center() noexcept { sendMessage(METALPP_SEL(center)); }

        void makeKeyAndOrderFront(const ns::Object& sender) noexcept
        {
            sendMessage(METALPP_SEL(makeKeyAndOrderFront_), sender.get());
        }

        void orderFront(const ns::Object& sender) noexcept
        {
            sendMessage(METALPP_SEL(orderFront_), sender.get());
        }

        void orderBack(const ns::Object& sender) noexcept
        {
            sendMessage(METALPP_SEL(orderBack_), sender.get());
        }

        void orderOut(const ns::Object& sender) noexcept
        {
            sendMessage(METALPP_SEL(orderOut_), sender.get());
        }

        void orderWindow(const WindowOrderingMode place, const ns::Integer otherWin)
        {
            sendMessage(METALPP_SEL(orderWindow_relativeTo_), place, otherWin);
        }

        void orderFrontRegardless() noexcept
        {
            sendMessage(METALPP_SEL(orderFrontRegardless));
        }

        [[nodiscard]] auto collectionBehavior() const noexcept API_AVAILABLE(macos(10.5))
        {
            return sendMessage<WindowCollectionBehavior>(METALPP_SEL(collectionBehavior));
        }

        void setCollectionBehavior(const WindowCollectionBehavior collectionBehavior) noexcept API_AVAILABLE(macos(10.5))
        {
            sendMessage(METALPP_SEL(setCollectionBehavior_), collectionBehavior);
        }

        [[nodiscard]] auto tabbingMode() const noexcept API_AVAILABLE(macos(10.12))
        {
            return sendMessage<WindowTabbingMode>(METALPP_SEL(tabbingMode));
        }

        void setTabbingMode(const WindowTabbingMode tabbingMode) noexcept API_AVAILABLE(macos(10.12))
        {
            sendMessage(METALPP_SEL(setTabbingMode_), tabbingMode);
        }

        [[nodiscard]] auto acceptsMouseMovedEvents() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(acceptsMouseMovedEvents)) == YES;
        }

        void setAcceptsMouseMovedEvents(const bool acceptsMouseMovedEvents) noexcept
        {
            sendMessage(METALPP_SEL(setAcceptsMouseMovedEvents_), acceptsMouseMovedEvents ? YES : NO);
        }

        [[nodiscard]] auto ignoresMouseEvents() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(ignoresMouseEvents)) == YES;
        }

        void setIgnoresMouseEvents(const bool ignoresMouseEvents) noexcept
        {
            sendMessage(METALPP_SEL(setIgnoresMouseEvents_), ignoresMouseEvents ? YES : NO);
        }
    };
}

#endif
