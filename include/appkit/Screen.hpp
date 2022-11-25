#ifndef METALPP_APPKIT_SCREEN_HPP
#define METALPP_APPKIT_SCREEN_HPP

#include "../objc/Object.hpp"
#include "../corefoundation/Types.h"
#include "Selectors.hpp"

namespace ns
{
    class Screen final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSScreen");
    public:
        static Screen mainScreen()
        {
            return Screen{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::mainScreen), sel::retain)};
        }

        static Screen deepestScreen()
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
