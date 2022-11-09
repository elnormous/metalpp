#ifndef METALPP_METAL_METAL_HPP
#define METALPP_METAL_METAL_HPP

#include <string>
#include <type_traits>
#include <objc/message.h>
#include <objc/runtime.h>
#include "Error.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

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
inline Ret sendMessage(id self, SEL selector, Args... args) noexcept
{
    if constexpr (reguiresFpret<Ret>::value)
    {
        using SendMessageFpretProc = Ret(id, SEL, Args...);
        SendMessageFpretProc* proc = reinterpret_cast<SendMessageFpretProc*>(&objc_msgSend_fpret);
        return proc(self, selector, args...);
    }
    else if constexpr (reguiresStret<Ret>::value)
    {
        using SendMessageStretProc = void(Ret*, id, SEL, Args...);
        SendMessageStretProc* proc = reinterpret_cast<SendMessageStretProc*>(&objc_msgSend_stret);
        Ret ret;
        proc(&ret, self, selector, args...);
        return ret;
    }
    else
    {
        using SendMessageProc = Ret(id, SEL, Args...);
        SendMessageProc* proc = reinterpret_cast<SendMessageProc*>(&objc_msgSend);
        return proc(self, selector, args...);
    }
}

namespace metal
{
    inline namespace detail
    {
        inline const auto retainSel = sel_registerName("retain");
        inline const auto releaseSel = sel_registerName("release");
    }

    class Device
    {
    public:
        Device():
            device{MTLCreateSystemDefaultDevice()}
        {
            if (!device)
                throw Error{"Failed to create Metal device"};
        }

        ~Device()
        {
            sendMessage(device, releaseSel);
        }

        Device(const Device& other) noexcept:
            device{other.device}
        {
            if (device)
                sendMessage(device, retainSel);
        }

        Device(Device&& other) noexcept:
            device{other.device}
        {
        }

        Device& operator=(const Device& other) noexcept
        {
            if (&other == this) return *this;
            if (device)
                sendMessage(device, releaseSel);
            device = other.device;
            if (device)
                sendMessage(device, retainSel);
            return *this;
        }

        Device& operator=(Device&& other) noexcept
        {
            if (&other == this) return *this;
            device = other.device;
            other.device = nil;
            return *this;
        }

        bool operator==(const Device& other) const noexcept
        {
            return device == other.device;
        }

        bool operator!=(const Device& other) const noexcept
        {
            return device != other.device;
        }

        operator id() const noexcept
        {
            return device;
        }

        std::string getName() const
        {
            id name = sendMessage<id>(device, sel_registerName("name"));
            const char* str = sendMessage<const char*, NSUInteger>(name, sel_registerName("cStringUsingEncoding:"), 1);
            return std::string{str};
        }

    private:
        id device = nil;
    };
}

#endif
