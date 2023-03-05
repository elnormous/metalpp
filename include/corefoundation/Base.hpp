#ifndef METALPP_COREFOUNDATION_BASE_HPP
#define METALPP_COREFOUNDATION_BASE_HPP

#include <CoreFoundation/CFBase.h>

namespace cf
{
    using TypeID = CFTypeID;
    using OptionFlags = CFOptionFlags;
    using HashCode = CFHashCode;
    using Index = CFIndex;

    using AllocatorContext = CFAllocatorContext;

    class Allocator final
    {
    public:
        [[nodiscard]] static auto defaultAllocator() noexcept
        {
            return Allocator{kCFAllocatorDefault};
        }

        [[nodiscard]] static auto systemDefaultAllocator() noexcept
        {
            return Allocator{kCFAllocatorSystemDefault};
        }

        [[nodiscard]] static auto mallocAllocator() noexcept
        {
            return Allocator{kCFAllocatorMalloc};
        }

        [[nodiscard]] static auto mallocZoneAllocator() noexcept
        {
            return Allocator{kCFAllocatorMallocZone};
        }

        [[nodiscard]] static auto nullAllocator() noexcept
        {
            return Allocator{kCFAllocatorNull};
        }

        [[nodiscard]] static auto userContextAllocator() noexcept
        {
            return Allocator{kCFAllocatorUseContext};
        }

        Allocator(const Allocator& allocator, AllocatorContext& context):
            ref{CFAllocatorCreate(allocator.ref, &context)}
        {
        }

        ~Allocator()
        {
            if (ref) CFRelease(ref);
        }

        Allocator(Allocator&& other) noexcept:
            ref{other.ref}
        {
            other.ref = nullptr;
        }

        Allocator(const Allocator& other) noexcept: ref{other.ref}
        {
            if (ref) CFRetain(ref);
        }

        Allocator& operator=(Allocator&& other) noexcept
        {
            if (&other == this) return *this;
            if (ref) CFRelease(ref);
            ref = other.ref;
            other.ref = nullptr;
            return *this;
        }

        Allocator& operator=(const Allocator& other) noexcept
        {
            if (&other == this) return *this;
            if (other.ref) CFRetain(other.ref);
            if (ref) CFRelease(ref);
            ref = other.ref;
            return *this;
        }

        Allocator(std::nullptr_t) noexcept {}
        Allocator(const CFAllocatorRef a) noexcept: ref{a}
        {
            if (ref) CFRetain(ref);
        }

        Allocator& operator=(std::nullptr_t) noexcept
        {
            if (ref) CFRetain(ref);
            ref = nullptr;
            return *this;
        }

        [[nodiscard]] operator CFAllocatorRef() const noexcept
        {
            return ref;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return ref;
        }

        [[nodiscard]] auto retainCount() const noexcept
        {
            return CFGetRetainCount(ref);
        }

        [[nodiscard]] void* allocate(const Index size, const OptionFlags hint) noexcept
        {
            return CFAllocatorAllocate(ref, size, hint);
        }

        void deallocate(void* ptr) noexcept
        {
            CFAllocatorDeallocate(ref, ptr);
        }

        [[nodiscard]] Index getPreferredSizeForSize(const Index size, const OptionFlags hint) const noexcept
        {
            return CFAllocatorGetPreferredSizeForSize(ref, size, hint);
        }

        [[nodiscard]] void* reallocate(void* ptr, const Index newsize, const OptionFlags hint) noexcept
        {
            return CFAllocatorReallocate(ref, ptr, newsize, hint);
        }

    private:
        CFAllocatorRef ref = nullptr;
    };
}

#endif
