#ifndef METALPP_APPKIT_SCREEN_HPP
#define METALPP_APPKIT_SCREEN_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../corefoundation/Types.hpp"
#include "../foundation/Array.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Screen final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSScreen");
    public:
        [[nodiscard]] static auto screens() noexcept
        {
            return Array<Screen>{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::screens), sel::retain)};
        }

        [[nodiscard]] static auto mainScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::mainScreen), sel::retain)};
        }

        [[nodiscard]] static auto deepestScreen() noexcept
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::deepestScreen), sel::retain)};
        }

        Screen() = delete;

        [[nodiscard]] auto frame() const noexcept
        {
            return sendMessage<cg::Rect>(sel::frame);
        }
    };
}

#endif
