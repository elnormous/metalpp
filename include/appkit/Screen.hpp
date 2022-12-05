#ifndef METALPP_APPKIT_SCREEN_HPP
#define METALPP_APPKIT_SCREEN_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/Array.hpp"
#include "../foundation/Geometry.hpp"

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

        [[nodiscard]] static auto screens() noexcept
        {
            return Array<Screen>{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(screens)), METALPP_SEL(retain))};
        }

        [[nodiscard]] static auto mainScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(mainScreen)), METALPP_SEL(retain))};
        }

        [[nodiscard]] static auto deepestScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(deepestScreen)), METALPP_SEL(retain))};
        }

        Screen() = delete;

        [[nodiscard]] auto frame() const noexcept
        {
            return sendMessage<ns::Rect>(METALPP_SEL(frame));
        }
    };
}

#endif
