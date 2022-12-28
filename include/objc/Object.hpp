#ifndef METALPP_OBJC_OBJECT_HPP
#define METALPP_OBJC_OBJECT_HPP

#include <cstdint>
#include <type_traits>
#include "Private.hpp"
#include "Runtime.hpp"

namespace ns
{
    struct Adopt { explicit Adopt() = default; };
    constexpr Adopt adopt;

    class Object
    {
    public:
        METALPP_PRIVATE_CLS("NSObject");

        METALPP_PRIVATE_SEL(getClass, "class");
        METALPP_PRIVATE_SEL(alloc, "alloc");
        METALPP_PRIVATE_SEL(init, "init");
        METALPP_PRIVATE_SEL(retain, "retain");
        METALPP_PRIVATE_SEL(release, "release");
        METALPP_PRIVATE_SEL(retainCount, "retainCount");
        METALPP_PRIVATE_SEL(autorelease, "autorelease");
        METALPP_PRIVATE_SEL(copy, "copy");

        Object() noexcept:
            ptr{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {
        }

        ~Object()
        {
            sendMessage(METALPP_SEL(release));
        }

        Object(const Object& other) noexcept:
            ptr{other.ptr}
        {
            sendMessage(METALPP_SEL(retain));
        }

        Object(Object&& other) noexcept:
            ptr{other.ptr}
        {
            other.ptr = nil;
        }

        Object& operator=(const Object& other) noexcept
        {
            if (&other == this) return *this;
            other.sendMessage(METALPP_SEL(retain));
            sendMessage(METALPP_SEL(release));
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

        Object(std::nullptr_t) noexcept {}
        Object(const id p) noexcept: ptr{p}
        {
            sendMessage(METALPP_SEL(retain));
        }
        Object(const id p, Adopt) noexcept: ptr{p} {}

        [[nodiscard]] bool operator==(const Object& other) const noexcept
        {
            return ptr == other.ptr;
        }

        [[nodiscard]] bool operator!=(const Object& other) const noexcept
        {
            return ptr != other.ptr;
        }

        [[nodiscard]] bool operator==(const id other) const noexcept
        {
            return ptr == other;
        }

        [[nodiscard]] bool operator!=(const id other) const noexcept
        {
            return ptr != other;
        }

        operator id() const noexcept
        {
            return ptr;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return ptr;
        }

        [[nodiscard]] auto getClass() const noexcept
        {
            return sendMessage<Class>(METALPP_SEL(getClass));
        }

        [[nodiscard]] auto retainCount() const noexcept
        {
            return sendMessage<UInteger>(METALPP_SEL(retainCount));
        }

        // Releases the ownership of the pointer without sending a release message
        [[nodiscard]] auto release() noexcept
        {
            const id result = ptr;
            ptr = nil;
            return result;
        }

    protected:
        template<typename Ret = void, typename... Args>
        Ret sendMessage(SEL selector, Args... args) const noexcept
        {
            return objc::sendMessage<Ret>(ptr, selector, args...);
        }

    private:
        id ptr = nil;
    };

    template<class Type>
    [[nodiscard]] std::enable_if_t<Type::copying, Type> copy(const Type& object) noexcept
    {
        return Type{objc::sendMessage<id>(object.get(), Object::METALPP_SEL(copy)), adopt};
    }
}

#endif
