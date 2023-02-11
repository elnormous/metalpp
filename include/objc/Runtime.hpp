#ifndef METALPP_OBJC_RUNTIME_HPP
#define METALPP_OBJC_RUNTIME_HPP

#include <climits>
#include <cstdint>
#include <type_traits>
#include <objc/NSObjCRuntime.h>
#include <objc/message.h>
#include <objc/runtime.h>

namespace ns
{
    using Integer = NSInteger;
    using UInteger = NSUInteger;

    constexpr Integer IntegerMax = NSIntegerMax;
    constexpr Integer IntegerMin = NSIntegerMin;
    constexpr UInteger UIntegerMax = NSUIntegerMax;

    enum class ComparisonResult: Integer
    {
        OrderedAscending = -1L,
        OrderedSame,
        OrderedDescending
    };
}

namespace objc
{
#if defined(__i386__) || defined(__x86_64__)
    template<typename Type>
    struct reguiresStret: std::bool_constant<(sizeof(Type) > (sizeof(std::uintptr_t) << 1))> {};
#elif defined(__arm__)
    template<typename Type>
    struct reguiresStret: std::bool_constant<(std::is_class_v<Type> && sizeof(Type) > sizeof(std::uintptr_t))> {};
#elif defined(__arm64__)
    template<typename Type>
    struct reguiresStret: std::false_type {};
#else
#  error "Unsupported architecture"
#endif

    template<>
    struct reguiresStret<void>: std::false_type {};

#if defined(__i386__)
    template<typename Type>
    struct reguiresFpret: std::bool_constant<is_floating_point_v<Type>> {};
#elif defined(__x86_64__)
    template<typename Type>
    struct reguiresFpret: std::bool_constant<std::is_same_v<Type, long double>> {};
#elif defined(__arm__) || defined(__arm64__)
    template<typename Type>
    struct reguiresFpret: std::false_type {};
#else
#  error "Unsupported architecture"
#endif

    template<typename Ret = void, typename... Args>
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

    template<typename Ret = void, typename... Args>
    static inline Ret sendSuperMessage(const void* self, SEL selector, Args... args) noexcept
    {
#if defined(__i386__) || defined(__x86_64__)
        if constexpr (reguiresStret<Ret>::value)
        {
            using SendMessageStretProc = void(Ret*, const void*, SEL, Args...);
            SendMessageStretProc* proc = reinterpret_cast<SendMessageStretProc*>(&objc_msgSendSuper_stret);
            Ret ret;
            proc(&ret, self, selector, args...);
            return ret;
        }
#endif
        using SendMessageProc = Ret(const void*, SEL, Args...);
        SendMessageProc* proc = reinterpret_cast<SendMessageProc*>(&objc_msgSendSuper);
        return proc(self, selector, args...);
    }
}

#endif
