#ifndef METALPP_METAL_COMMANDBUFFER_HPP
#define METALPP_METAL_COMMANDBUFFER_HPP

#include "../objc/Object.hpp"

namespace mtl
{
    class CommandBuffer: public ns::Object
    {
    public:
        CommandBuffer(const id p) noexcept: ns::Object{p} {}

    };
}

#endif
