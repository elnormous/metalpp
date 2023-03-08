#ifndef METALPP_COREFOUNDATION_DICTIONARY_HPP
#define METALPP_COREFOUNDATION_DICTIONARY_HPP

#include <CoreFoundation/CFDictionary.h>
#include "Base.hpp"

namespace cf
{
    using DictionaryKeyCallBacks = CFDictionaryKeyCallBacks;
    using DictionaryValueCallBacks = CFDictionaryValueCallBacks;

    class Dictionary final
    {
    public:
        Dictionary(const Allocator& allocator,
                   const void** keys,
                   const void** values,
                   CFIndex numValues,
                   const DictionaryKeyCallBacks* keyCallBacks = nullptr,
                   const DictionaryValueCallBacks* valueCallBacks = nullptr):
            ref{CFDictionaryCreate(allocator, keys, values, numValues, keyCallBacks, valueCallBacks)}
        {
        }

        ~Dictionary()
        {
            if (ref) CFRelease(ref);
        }

        Dictionary(Dictionary&& other) noexcept:
            ref{other.ref}
        {
            other.ref = nullptr;
        }

        Dictionary(const Dictionary& other) noexcept: ref{other.ref}
        {
            if (ref) CFRetain(ref);
        }

        Dictionary& operator=(Dictionary&& other) noexcept
        {
            if (&other == this) return *this;
            if (ref) CFRelease(ref);
            ref = other.ref;
            other.ref = nullptr;
            return *this;
        }

        Dictionary& operator=(const Dictionary& other) noexcept
        {
            if (&other == this) return *this;
            if (other.ref) CFRetain(other.ref);
            if (ref) CFRelease(ref);
            ref = other.ref;
            return *this;
        }

        Dictionary(std::nullptr_t) noexcept {}
        Dictionary(const CFDictionaryRef a) noexcept: ref{a}
        {
            if (ref) CFRetain(ref);
        }

        Dictionary& operator=(std::nullptr_t) noexcept
        {
            if (ref) CFRelease(ref);
            ref = nullptr;
            return *this;
        }

        [[nodiscard]] operator CFDictionaryRef() const noexcept
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

    private:
        CFDictionaryRef ref = nullptr;
    };
}

#endif
