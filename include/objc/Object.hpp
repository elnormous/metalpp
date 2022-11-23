#ifndef METALPP_OBJC_OBJECT_HPP
#define METALPP_OBJC_OBJECT_HPP

#include <cstdint>
#include <type_traits>
#include "Runtime.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Object
    {
        static inline const auto cls = objc_lookUpClass("NSObject");
    public:
        Object() noexcept:
            ptr{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        ~Object()
        {
            sendMessage(sel::release);
        }

        Object(const Object& other) noexcept:
            ptr{other.ptr}
        {
            sendMessage(sel::retain);
        }

        Object(Object&& other) noexcept:
            ptr{other.ptr}
        {
            other.ptr = nil;
        }

        Object& operator=(const Object& other) noexcept
        {
            if (&other == this) return *this;
            other.sendMessage(sel::retain);
            sendMessage(sel::release);
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

        Object(const id p) noexcept: ptr{p} {}

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

        [[nodiscard]] Class getClass() const noexcept
        {
            return sendMessage<Class>(sel::getClass);
        }

        [[nodiscard]] UInteger retainCount() const noexcept
        {
            return sendMessage<UInteger>(sel::retainCount);
        }

        // Releases the ownership of the pointer without sending a release message
        [[nodiscard]] id release() noexcept
        {
            const id result = ptr;
            ptr = nil;
            return result;
        }

    protected:
        template <typename Ret = void, typename... Args>
        Ret sendMessage(SEL selector, Args... args) const noexcept
        {
            return objc::sendMessage<Ret>(ptr, selector, args...);
        }

        template <typename Ret, typename... Args>
        std::enable_if_t<std::is_base_of_v<Object, Ret>, Ret> getRetained(SEL selector, Args... args) const noexcept
        {
            const id object = objc::sendMessage<id>(ptr, selector, args...);
            return Ret{objc::sendMessage<id>(object, sel::retain)};
        }

    private:
        id ptr = nil;
    };
}

#endif
