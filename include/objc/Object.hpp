#ifndef METALPP_OBJC_OBJECT_HPP
#define METALPP_OBJC_OBJECT_HPP

#include "Runtime.hpp"

namespace ns
{
    inline namespace detail
    {
        inline const auto allocSel = sel_registerName("alloc");
        inline const auto initSel = sel_registerName("init");
        inline const auto retainSel = sel_registerName("retain");
        inline const auto releaseSel = sel_registerName("release");
        inline const auto retainCountSel = sel_registerName("retainCount");
    }

    class Object
    {
    public:
        Object() noexcept
        {
        }
        
        Object(const id p, const bool retain = true) noexcept: ptr{p}
        {
            if (ptr && retain)
                objc::sendMessage(ptr, retainSel);
        }

        ~Object()
        {
            if (ptr)
                objc::sendMessage(ptr, releaseSel);
        }

        Object(const Object& other) noexcept:
            ptr{other.ptr}
        {
            if (ptr)
                objc::sendMessage(ptr, retainSel);
        }

        Object(Object&& other) noexcept:
            ptr{other.ptr}
        {
        }

        Object& operator=(const Object& other) noexcept
        {
            if (&other == this) return *this;
            if (ptr)
                objc::sendMessage(ptr, releaseSel);
            ptr = other.ptr;
            if (ptr)
                objc::sendMessage(ptr, retainSel);
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
            const NSUInteger count = objc::sendMessage<NSUInteger>(ptr, retainCountSel);
            return static_cast<std::size_t>(count);
        }

    private:
        id ptr = nil;
    };
}

#endif
