#ifndef METALPP_METAL_COMMANDQUEUE_HPP
#define METALPP_METAL_COMMANDQUEUE_HPP

#include "../objc/Object.hpp"
#include "Classes.hpp"

namespace mtl
{
    class CommandQueue: public ns::Object
    {
    public:
        CommandQueue() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls::commandQueue, ns::sel::alloc), ns::sel::init)}
        {
        }

        CommandQueue(const id p) noexcept: Object{p} {}
    };
}

#endif
