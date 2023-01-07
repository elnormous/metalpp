#ifndef METALPP_METAL_COMPUTECOMMANDENCODER_HPP
#define METALPP_METAL_COMPUTECOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "CommandEncoder.hpp"

namespace mtl
{
    class ComputeCommandEncoder final: public CommandEncoder
    {
    public:
        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        ComputeCommandEncoder() = delete;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
