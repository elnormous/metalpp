#ifndef METALPP_APPKIT_EVENT_HPP
#define METALPP_APPKIT_EVENT_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Date.hpp"
#include "../foundation/Geometry.hpp"

namespace ns
{
    class Window;

    enum class EventType: UInteger
    {
        LeftMouseDown             = 1,
        LeftMouseUp               = 2,
        RightMouseDown            = 3,
        RightMouseUp              = 4,
        MouseMoved                = 5,
        LeftMouseDragged          = 6,
        RightMouseDragged         = 7,
        MouseEntered              = 8,
        MouseExited               = 9,
        KeyDown                   = 10,
        KeyUp                     = 11,
        FlagsChanged              = 12,
        AppKitDefined             = 13,
        SystemDefined             = 14,
        ApplicationDefined        = 15,
        Periodic                  = 16,
        CursorUpdate              = 17,
        ScrollWheel               = 22,
        TabletPoint               = 23,
        TabletProximity           = 24,
        OtherMouseDown            = 25,
        OtherMouseUp              = 26,
        OtherMouseDragged         = 27,
        /* The following event types are available on some hardware on 10.5.2 and later */
        Gesture API_AVAILABLE(macos(10.5))       = 29,
        Magnify API_AVAILABLE(macos(10.5))       = 30,
        Swipe   API_AVAILABLE(macos(10.5))       = 31,
        Rotate  API_AVAILABLE(macos(10.5))       = 18,
        BeginGesture API_AVAILABLE(macos(10.5))  = 19,
        EndGesture API_AVAILABLE(macos(10.5))    = 20,

        SmartMagnify API_AVAILABLE(macos(10.8)) = 32,
        QuickLook API_AVAILABLE(macos(10.8)) = 33,

        Pressure API_AVAILABLE(macos(10.10.3)) = 34,
        DirectTouch API_AVAILABLE(macos(10.10)) = 37,

        ChangeMode API_AVAILABLE(macos(10.15)) = 38,
    };

    enum class EventModifierFlags: UInteger
    {
        None               = 0,
        CapsLock           = 1 << 16, // Set if Caps Lock key is pressed.
        Shift              = 1 << 17, // Set if Shift key is pressed.
        Control            = 1 << 18, // Set if Control key is pressed.
        Option             = 1 << 19, // Set if Option or Alternate key is pressed.
        Command            = 1 << 20, // Set if Command key is pressed.
        NumericPad         = 1 << 21, // Set if any key in the numeric keypad is pressed.
        Help               = 1 << 22, // Set if the Help key is pressed.
        Function           = 1 << 23, // Set if any function key is pressed.

        // Used to retrieve only the device-independent modifier flags, allowing applications to mask off the device-dependent modifier flags, including event coalescing information.
        DeviceIndependentFlagsMask    = 0xffff0000UL
    };

    [[nodiscard]] inline constexpr EventModifierFlags operator&(const EventModifierFlags a, const EventModifierFlags b) noexcept
    {
        return static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) & static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    [[nodiscard]] inline constexpr EventModifierFlags operator|(const EventModifierFlags a, const EventModifierFlags b) noexcept
    {
        return static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) | static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    [[nodiscard]] inline constexpr EventModifierFlags operator^(const EventModifierFlags a, const EventModifierFlags b) noexcept
    {
        return static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) ^ static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    [[nodiscard]] inline constexpr EventModifierFlags operator~(const EventModifierFlags a) noexcept
    {
        return static_cast<EventModifierFlags>(~static_cast<std::underlying_type_t<EventModifierFlags>>(a));
    }
    inline constexpr EventModifierFlags& operator&=(EventModifierFlags& a, const EventModifierFlags b) noexcept
    {
        return a = static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) & static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    inline constexpr EventModifierFlags& operator|=(EventModifierFlags& a, const EventModifierFlags b) noexcept
    {
        return a = static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) | static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    inline constexpr EventModifierFlags& operator^=(EventModifierFlags& a, const EventModifierFlags b) noexcept
    {
        return a = static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) ^ static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }

    class Event: public Object
    {
    public:
        static constexpr bool copying = true;
        
        METALPP_PRIVATE_CLS("NSEvent");

        METALPP_PRIVATE_SEL(type, "type");
        METALPP_PRIVATE_SEL(modifierFlags, "modifierFlags");
        METALPP_PRIVATE_SEL(timestamp, "timestamp");
        METALPP_PRIVATE_SEL(window, "window");
        METALPP_PRIVATE_SEL(windowNumber, "windowNumber");
        METALPP_PRIVATE_SEL(clickCount, "clickCount");
        METALPP_PRIVATE_SEL(buttonNumber, "buttonNumber");
        METALPP_PRIVATE_SEL(eventNumber, "eventNumber");
        METALPP_PRIVATE_SEL(pressure, "pressure");
        METALPP_PRIVATE_SEL(locationInWindow, "locationInWindow");
        METALPP_PRIVATE_SEL(deltaX, "deltaX");
        METALPP_PRIVATE_SEL(deltaY, "deltaY");
        METALPP_PRIVATE_SEL(deltaZ, "deltaZ");
        METALPP_PRIVATE_SEL(keyCode, "keyCode");

        using Object::Object;
        using Object::operator=;

        Event() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        [[nodiscard]] auto type() const noexcept
        {
            return sendMessage<EventType>(METALPP_SEL(type));
        }

        [[nodiscard]] auto modifierFlags() const noexcept
        {
            return sendMessage<EventModifierFlags>(METALPP_SEL(modifierFlags));
        }

        [[nodiscard]] auto timestamp() const noexcept
        {
            return sendMessage<TimeInterval>(METALPP_SEL(timestamp));
        }

        [[nodiscard]] Window window() const noexcept;

        [[nodiscard]] auto windowNumber() const noexcept
        {
            return sendMessage<Integer>(METALPP_SEL(windowNumber));
        }

        [[nodiscard]] auto clickCount() const noexcept
        {
            return sendMessage<Integer>(METALPP_SEL(clickCount));
        }

        [[nodiscard]] auto buttonNumber() const noexcept
        {
            return sendMessage<Integer>(METALPP_SEL(buttonNumber));
        }

        [[nodiscard]] auto eventNumber() const noexcept
        {
            return sendMessage<Integer>(METALPP_SEL(eventNumber));
        }

        [[nodiscard]] auto pressure() const noexcept
        {
            return sendMessage<float>(METALPP_SEL(pressure));
        }

        [[nodiscard]] auto locationInWindow() const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(locationInWindow));
        }

        [[nodiscard]] auto deltaX() const noexcept
        {
            return sendMessage<cg::Float>(METALPP_SEL(deltaX));
        }

        [[nodiscard]] auto deltaY() const noexcept
        {
            return sendMessage<cg::Float>(METALPP_SEL(deltaY));
        }

        [[nodiscard]] auto deltaZ() const noexcept
        {
            return sendMessage<cg::Float>(METALPP_SEL(deltaZ));
        }

        [[nodiscard]] auto keyCode() const noexcept
        {
            return sendMessage<unsigned short>(METALPP_SEL(keyCode));
        }
    };
}

#endif
