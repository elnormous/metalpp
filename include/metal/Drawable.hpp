#ifndef METALPP_METAL_DRAWABLE_HPP
#define METALPP_METAL_DRAWABLE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Drawable: public ns::Object
    {
    public:
        Drawable() = delete;

        void present() noexcept
        {
            sendMessage(sel::present);
        }

        void present(const CFTimeInterval presentationTime) noexcept
        {
            sendMessage(sel::presentAtTime_, presentationTime);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
