#ifndef METALPP_OBJC_OBJECT_HPP
#define METALPP_OBJC_OBJECT_HPP

#include "Classes.hpp"
#include "Runtime.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Object
    {
    public:
        Object() noexcept:
            ptr{objc::sendMessage<id>(objc::sendMessage<id>(objc::objectClass, objc::allocSel), objc::initSel)}
        {
        }

        ~Object()
        {
            objc::sendMessage(ptr, objc::releaseSel);
        }

        Object(const Object& other) noexcept:
            ptr{other.ptr}
        {
            objc::sendMessage(ptr, objc::retainSel);
        }

        Object(Object&& other) noexcept:
            ptr{other.ptr}
        {
            other.ptr = nil;
        }

        Object& operator=(const Object& other) noexcept
        {
            if (&other == this) return *this;
            objc::sendMessage(other.ptr, objc::retainSel);
            objc::sendMessage(ptr, objc::releaseSel);
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

        operator id() const noexcept
        {
            return ptr;
        }

        std::size_t retainCount() const noexcept
        {
            const auto retainCount = objc::sendMessage<NSUInteger>(ptr, objc::retainCountSel);
            return static_cast<std::size_t>(retainCount);
        }

    protected:
        Object(const id p) noexcept: ptr{p}
        {
        }

    private:
        id ptr = nil;
    };
}

#endif
