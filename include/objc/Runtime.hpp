#ifndef METALPP_OBJC_RUNTIME_HPP
#define METALPP_OBJC_RUNTIME_HPP

#include <cstdint>
#include <type_traits>
#include <objc/message.h>
#include <objc/runtime.h>

namespace objc
{
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
    inline Ret sendMessage(const void* self, SEL selector, Args... args) noexcept
    {
        if constexpr (reguiresFpret<Ret>::value)
        {
            using SendMessageFpretProc = Ret(const void*, SEL, Args...);
            SendMessageFpretProc* proc = reinterpret_cast<SendMessageFpretProc*>(&objc_msgSend_fpret);
            return proc(self, selector, args...);
        }
        else if constexpr (reguiresStret<Ret>::value)
        {
            using SendMessageStretProc = void(Ret*, const void*, SEL, Args...);
            SendMessageStretProc* proc = reinterpret_cast<SendMessageStretProc*>(&objc_msgSend_stret);
            Ret ret;
            proc(&ret, self, selector, args...);
            return ret;
        }
        else
        {
            using SendMessageProc = Ret(const void*, SEL, Args...);
            SendMessageProc* proc = reinterpret_cast<SendMessageProc*>(&objc_msgSend);
            return proc(self, selector, args...);
        }
    }
}

#endif
