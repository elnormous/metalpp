#ifndef METALPP_OBJC_OBJECT_HPP
#define METALPP_OBJC_OBJECT_HPP

#include <cstdint>
#include <type_traits>
#include <objc/message.h>
#include <objc/runtime.h>
#include "Runtime.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Object
    {
        static inline const auto cls = objc_lookUpClass("NSObject");
    public:
        Object() noexcept:
            ptr{sendMessage<id>(sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        ~Object()
        {
            sendMessage(ptr, sel::release);
        }

        Object(const Object& other) noexcept:
            ptr{other.ptr}
        {
            sendMessage(ptr, sel::retain);
        }

        Object(Object&& other) noexcept:
            ptr{other.ptr}
        {
            other.ptr = nil;
        }

        Object& operator=(const Object& other) noexcept
        {
            if (&other == this) return *this;
            sendMessage(other.ptr, sel::retain);
            sendMessage(ptr, sel::release);
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

        Object(const id p) noexcept: ptr{p}
        {
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

        [[nodiscard]] Class getClass() const noexcept
        {
            return sendMessage<Class>(ptr, sel::getClass);
        }

        [[nodiscard]] UInteger retainCount() const noexcept
        {
            return sendMessage<UInteger>(ptr, sel::retainCount);
        }

        // Releases the ownership of the pointer without sending a release message
        [[nodiscard]] id release() noexcept
        {
            id result = ptr;
            ptr = nil;
            return result;
        }

    protected:
#if defined(__i386__) || defined(__x86_64__)
    template <typename Type>
    struct reguiresStret: std::bool_constant<(sizeof(Type) > (sizeof(std::uintptr_t) << 1))> {};
#elif defined(__arm__)
    template <typename Type>
    struct reguiresStret: std::bool_constant<(std::is_class_v<Type> && sizeof(Type) > sizeof(std::uintptr_t))> {};
#elif defined(__arm64__)
    template <typename Type>
    struct reguiresStret: std::false_type {};
#else
#  error "Unsupported architecture"
#endif

    template <>
    struct reguiresStret<void>: std::false_type {};

#if defined(__i386__)
    template <typename Type>
    struct reguiresFpret: std::bool_constant<is_floating_point_v<Type>> {};
#elif defined(__x86_64__)
    template <typename Type>
    struct reguiresFpret: std::bool_constant<std::is_same_v<Type, long double>> {};
#elif defined(__arm__) || defined(__arm64__)
    template <typename Type>
    struct reguiresFpret: std::false_type {};
#else
#  error "Unsupported architecture"
#endif

    template <typename Ret = void, typename... Args>
    static inline Ret sendMessage(const void* self, SEL selector, Args... args) noexcept
    {
#if defined(__i386__) || defined(__x86_64__) || defined(__arm__)
        if constexpr (reguiresFpret<Ret>::value)
        {
            using SendMessageFpretProc = Ret(const void*, SEL, Args...);
            SendMessageFpretProc* proc = reinterpret_cast<SendMessageFpretProc*>(&objc_msgSend_fpret);
            return proc(self, selector, args...);
        }
#endif
#if defined(__i386__) || defined(__x86_64__)
        if constexpr (reguiresStret<Ret>::value)
        {
            using SendMessageStretProc = void(Ret*, const void*, SEL, Args...);
            SendMessageStretProc* proc = reinterpret_cast<SendMessageStretProc*>(&objc_msgSend_stret);
            Ret ret;
            proc(&ret, self, selector, args...);
            return ret;
        }
#endif
        using SendMessageProc = Ret(const void*, SEL, Args...);
        SendMessageProc* proc = reinterpret_cast<SendMessageProc*>(&objc_msgSend);
        return proc(self, selector, args...);
    }

    template <typename Ret = void, typename... Args>
    Ret sendMessage(SEL selector, Args... args) const noexcept
    {
        return sendMessage<Ret>(ptr, selector, args...);
    }

    template <typename Ret, typename... Args>
    std::enable_if_t<std::is_base_of_v<Object, Ret>, Ret> getRetained(SEL selector, Args... args) const noexcept
    {
        const id object = sendMessage<id>(ptr, selector, args...);
        return Ret{sendMessage<id>(object, sel::retain)};
    }

    private:
        id ptr = nil;
    };
}

#endif
