#ifndef METALPP_APPKIT_EVENT_HPP
#define METALPP_APPKIT_EVENT_HPP

#include "../objc/Runtime.hpp"

namespace ns
{
    enum class EventModifierFlags: ns::UInteger
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

    inline constexpr EventModifierFlags operator&(const EventModifierFlags a, const EventModifierFlags b) noexcept
    {
        return static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) & static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    inline constexpr EventModifierFlags operator|(const EventModifierFlags a, const EventModifierFlags b) noexcept
    {
        return static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) | static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    inline constexpr EventModifierFlags operator^(const EventModifierFlags a, const EventModifierFlags b) noexcept
    {
        return static_cast<EventModifierFlags>(static_cast<std::underlying_type_t<EventModifierFlags>>(a) ^ static_cast<std::underlying_type_t<EventModifierFlags>>(b));
    }
    inline constexpr EventModifierFlags operator~(const EventModifierFlags a) noexcept
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
}

#endif
