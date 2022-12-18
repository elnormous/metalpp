#ifndef METALPP_METAL_DRAWABLE_HPP
#define METALPP_METAL_DRAWABLE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"

namespace mtl
{
    class Drawable: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(present, "present");
        METALPP_PRIVATE_SEL(presentAtTime_, "presentAtTime:");

        using Object::Object;

        Drawable() = delete;

        void present() noexcept
        {
            sendMessage(METALPP_SEL(present));
        }

        void present(const CFTimeInterval presentationTime) noexcept
        {
            sendMessage(METALPP_SEL(presentAtTime_), presentationTime);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
