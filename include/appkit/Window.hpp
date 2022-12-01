#ifndef METALPP_APPKIT_WINDOW_HPP
#define METALPP_APPKIT_WINDOW_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/Geometry.hpp"
#include "Graphics.hpp"
#include "Screen.hpp"
#include "Selectors.hpp"

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
    
    class Window final: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSWindow");

        using Object::Object;
        Window() = delete;

        Window(const Rect contentRect, const WindowStyleMask style, const BackingStoreType backingStoreType, bool defer) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc),
                                         ns::sel::initWithContentRect_styleMask_backing_defer_,
                                         contentRect,
                                         style,
                                         backingStoreType,
                                         defer ? YES : NO)}
        {
        }

        Window(const Rect contentRect, const WindowStyleMask style, const BackingStoreType backingStoreType, bool defer, const Screen& screen) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc),
                                         ns::sel::initWithContentRect_styleMask_backing_defer_screen_,
                                         contentRect,
                                         style,
                                         backingStoreType,
                                         defer ? YES : NO,
                                         screen.get())}
        {
        }
    };
}

#endif
