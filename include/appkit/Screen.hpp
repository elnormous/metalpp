#ifndef METALPP_APPKIT_SCREEN_HPP
#define METALPP_APPKIT_SCREEN_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/Array.hpp"
#include "../foundation/Dictionary.hpp"
#include "../foundation/Geometry.hpp"
#include "Graphics.hpp"

namespace ns
{
    class Screen final: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSScreen");
        
        METALPP_PRIVATE_SEL(screens, "screens");
        METALPP_PRIVATE_SEL(mainScreen, "mainScreen");
        METALPP_PRIVATE_SEL(deepestScreen, "deepestScreen");
        METALPP_PRIVATE_SEL(frame, "frame");
        METALPP_PRIVATE_SEL(deviceDescription, "deviceDescription");

        using Object::Object;
        using Object::operator=;

        [[nodiscard]] static auto screens() noexcept
        {
            return Array<Screen>{objc::sendMessage<id>(cls, METALPP_SEL(screens))};
        }

        [[nodiscard]] static auto mainScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(cls, METALPP_SEL(mainScreen))};
        }

        [[nodiscard]] static auto deepestScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(cls, METALPP_SEL(deepestScreen))};
        }

        Screen() = delete;

        [[nodiscard]] auto frame() const noexcept
        {
            return sendMessage<Rect>(METALPP_SEL(frame));
        }

        [[nodiscard]] auto deviceDescription() const noexcept
        {
            return Dictionary<DeviceDescriptionKey, Object>{sendMessage<id>(METALPP_SEL(deviceDescription))};
        }
    };
}

#endif
