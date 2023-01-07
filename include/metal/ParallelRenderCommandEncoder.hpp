#ifndef METALPP_METAL_PARALLELRENDERCOMMANDENCODER_HPP
#define METALPP_METAL_PARALLELRENDERCOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "CommandEncoder.hpp"
#include "RenderCommandEncoder.hpp"

namespace mtl
{
    class ParallelRenderCommandEncoder final: public CommandEncoder
    {
    public:
        METALPP_PRIVATE_SEL(renderCommandEncoder, "renderCommandEncoder");

        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        ParallelRenderCommandEncoder() = delete;

        [[nodiscard]] auto renderCommandEncoder() const noexcept
        {
            return RenderCommandEncoder{sendMessage<id>(METALPP_SEL(renderCommandEncoder))};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
