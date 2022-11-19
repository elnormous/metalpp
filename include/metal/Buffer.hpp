#ifndef METALPP_METAL_BUFFER_HPP
#define METALPP_METAL_BUFFER_HPP

#include <os/availability.h>
#include "../foundation/Selectors.hpp"
#include "Resource.hpp"

namespace mtl
{
    class Buffer: public Resource
    {
    public:
        Buffer() = delete;

        [[nodiscard]] std::size_t length() const noexcept
        {
            const auto length = objc::sendMessage<NSUInteger>(*this, ns::sel::length);
            return static_cast<std::size_t>(length);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
