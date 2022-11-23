#ifndef METALPP_METAL_BUFFER_HPP
#define METALPP_METAL_BUFFER_HPP

#include <os/availability.h>
#include "../foundation/Selectors.hpp"
#include "../foundation/Range.hpp"
#include "Resource.hpp"

namespace mtl
{
    class Buffer: public Resource
    {
    public:
        Buffer() = delete;

        [[nodiscard]] auto length() const noexcept
        {
            return sendMessage<ns::UInteger>(ns::sel::length);
        }

        [[nodiscard]] auto contents() const noexcept
        {
            return sendMessage<void*>(sel::contents);
        }

        void didModifyRange(const ns::Range& range) const noexcept API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios)
        {
            sendMessage(sel::didModifyRange_, range);
        }

        [[nodiscard]] auto gpuAddress() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<uint64_t>(sel::gpuAddress);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
