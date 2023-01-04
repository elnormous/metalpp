#ifndef METALPP_METAL_COMMANDENCODER_HPP
#define METALPP_METAL_COMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class Device;

    enum class ResourceUsage: ns::UInteger
    {
        Read   = 1 << 0,
        Write  = 1 << 1,
        Sample API_DEPRECATED_WITH_REPLACEMENT("Read", macos(10.13, 13.0), ios(11.0, 16.0)) = 1 << 2
    } API_AVAILABLE(macos(10.13), ios(11.0));

    enum class BarrierScope: ns::UInteger
    {
        Buffers = 1 << 0,
        Textures = 1 << 1,
        RenderTargets API_AVAILABLE(macos(10.14), macCatalyst(13.0)) API_UNAVAILABLE(ios) = 1 << 2,
    } API_AVAILABLE(macos(10.14), ios(12.0));

    class CommandEncoder: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(endEncoding, "endEncoding");
        METALPP_PRIVATE_SEL(insertDebugSignpost_, "insertDebugSignpost:");
        METALPP_PRIVATE_SEL(pushDebugGroup_, "pushDebugGroup:");
        METALPP_PRIVATE_SEL(popDebugGroup, "popDebugGroup");

        using Object::Object;
        using Object::operator=;

        CommandEncoder() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }
        
        void endEncoding() noexcept
        {
            sendMessage(METALPP_SEL(endEncoding));
        }

        void insertDebugSignpost(const ns::String& string) noexcept
        {
            sendMessage(METALPP_SEL(insertDebugSignpost_), string.get());
        }

        void pushDebugGroup(const ns::String& string) noexcept
        {
            sendMessage(METALPP_SEL(pushDebugGroup_), string.get());
        }

        void popDebugGroup() noexcept
        {
            sendMessage(METALPP_SEL(popDebugGroup));
        }
    };
}

#endif
