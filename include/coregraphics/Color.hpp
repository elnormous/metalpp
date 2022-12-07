#ifndef METALPP_APPKIT_COLOR_HPP
#define METALPP_APPKIT_COLOR_HPP

#include <CoreGraphics/CGColor.h>
#include "../corefoundation/Types.hpp"
#include "ColorSpace.hpp"

namespace cg
{
    class Color final
    {
    public:
        Color(const ColorSpace& colorSpace, const Float* components) noexcept:
            ref{CGColorCreate(colorSpace, components)}
        {}

        Color(CGColorRef r) noexcept: ref{r} {}

        ~Color()
        {
            CGColorRelease(ref);
        }

        Color(Color&& other) noexcept:
            ref{other.ref}
        {
            other.ref = nullptr;
        }

        Color(const Color& other) noexcept:
            ref{other.ref}
        {
            CGColorRetain(ref);
        }

        Color& operator=(Color&& other) noexcept
        {
            if (&other == this) return *this;
            CGColorRelease(ref);
            ref = other.ref;
            other.ref = nullptr;
            return *this;
        }

        Color& operator=(const Color& other) noexcept
        {
            if (&other == this) return *this;
            CGColorRetain(other.ref);
            CGColorRelease(ref);
            ref = other.ref;
            return *this;
        }

        [[nodiscard]] operator CGColorRef() const noexcept
        {
            return ref;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return ref;
        }
        
        [[nodiscard]] auto retainCount() const noexcept
        {
            return ref ? CFGetRetainCount(ref) : 0;
        }

    private:
        CGColorRef ref = nullptr;
    };
}

#endif
