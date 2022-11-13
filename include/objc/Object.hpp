#ifndef METALPP_OBJC_OBJECT_HPP
#define METALPP_OBJC_OBJECT_HPP

#include <objc/NSObjCRuntime.h>
#include "Classes.hpp"
#include "Runtime.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Object
    {
    public:
        Object() noexcept:
            ptr{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::object, ns::sel::alloc), ns::sel::init)}
        {
        }

        ~Object()
        {
            objc::sendMessage(ptr, ns::sel::release);
        }

        Object(const Object& other) noexcept:
            ptr{other.ptr}
        {
            objc::sendMessage(ptr, ns::sel::retain);
        }

        Object(Object&& other) noexcept:
            ptr{other.ptr}
        {
            other.ptr = nil;
        }

        Object& operator=(const Object& other) noexcept
        {
            if (&other == this) return *this;
            objc::sendMessage(other.ptr, ns::sel::retain);
            objc::sendMessage(ptr, ns::sel::release);
            ptr = other.ptr;
            return *this;
        }

        Object& operator=(Object&& other) noexcept
        {
            if (&other == this) return *this;
            ptr = other.ptr;
            other.ptr = nil;
            return *this;
        }

        bool operator==(const Object& other) const noexcept
        {
            return ptr == other.ptr;
        }

        bool operator!=(const Object& other) const noexcept
        {
            return ptr != other.ptr;
        }

        Object(const id p) noexcept: ptr{p}
        {
        }

        operator id() const noexcept
        {
            return ptr;
        }

        std::size_t retainCount() const noexcept
        {
            const auto retainCount = objc::sendMessage<NSUInteger>(ptr, ns::sel::retainCount);
            return static_cast<std::size_t>(retainCount);
        }

        // Releases the ownership of the pointer without sending a release message
        id release() noexcept
        {
            id result = ptr;
            ptr = nil;
            return result;
        }

    private:
        id ptr = nil;
    };
}

#endif
