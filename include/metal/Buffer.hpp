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

        [[nodiscard]] NSUInteger length() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, ns::sel::length);
        }

        [[nodiscard]] void* contents() const noexcept
        {
            return objc::sendMessage<void*>(*this, sel::contents);
        }

        void didModifyRange(const ns::Range& range) const noexcept API_AVAILABLE(macos(10.11), macCatalyst(13.0)) API_UNAVAILABLE(ios)
        {
            objc::sendMessage(*this, sel::didModifyRange_, range);
        }

        [[nodiscard]] uint64_t gpuAddress() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return objc::sendMessage<uint64_t>(*this, sel::gpuAddress);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
