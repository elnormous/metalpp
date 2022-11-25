#ifndef METALPP_APPKIT_SCREEN_HPP
#define METALPP_APPKIT_SCREEN_HPP

#include "../objc/Object.hpp"
#include "../corefoundation/Types.hpp"
#include "../foundation/Array.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Screen final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSScreen");
    public:
        static Array<Screen> screens() noexcept
        {
            return Array<Screen>{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::screens), sel::retain)};
        }

        static Screen mainScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::mainScreen), sel::retain)};
        }

        static Screen deepestScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::deepestScreen), sel::retain)};
        }

        Screen() = delete;

        auto frame() const noexcept
        {
            return sendMessage<cg::Rect>(sel::frame);
        }
    };
}

#endif
