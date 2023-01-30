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
        METALPP_PRIVATE_SEL(presentedTime, "presentedTime");
        METALPP_PRIVATE_SEL(drawableID, "drawableID");

        using Object::Object;
        using Object::operator=;

        Drawable() = delete;

        void present() noexcept
        {
            sendMessage(METALPP_SEL(present));
        }

        void present(const CFTimeInterval presentationTime) noexcept
        {
            sendMessage(METALPP_SEL(presentAtTime_), presentationTime);
        }

        [[nodiscard]] auto presentedTime() const noexcept API_AVAILABLE(macos(10.15.4), ios(10.3), macCatalyst(13.4))
        {
            return sendMessage<CFTimeInterval>(METALPP_SEL(presentedTime));
        }

        [[nodiscard]] auto drawableID() const noexcept API_AVAILABLE(macos(10.15.4), ios(10.3), macCatalyst(13.4))
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(drawableID));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
