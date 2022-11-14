#ifndef METALPP_METAL_COMMANDQUEUE_HPP
#define METALPP_METAL_COMMANDQUEUE_HPP

#include "../objc/Object.hpp"
#include "Classes.hpp"

namespace mtl
{
    class Device;

    class CommandQueue: public ns::Object
    {
    public:
        CommandQueue() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls::commandQueue, ns::sel::alloc), ns::sel::init)}
        {
        }

        CommandQueue(const id p) noexcept: Object{p} {}

        Device device() const noexcept;
        
        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String& label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }
    };
}

#endif
