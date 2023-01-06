#ifndef METALPP_COREGRAPHICS_COLORSPACE_HPP
#define METALPP_COREGRAPHICS_COLORSPACE_HPP

#include <CoreGraphics/CGColorSpace.h>

namespace cg
{
    class ColorSpace final
    {
    public:
        [[nodiscard]] static auto deviceGray() noexcept
        {
            return ColorSpace{CGColorSpaceCreateDeviceGray()};
        }

        [[nodiscard]] static auto deviceRGB() noexcept
        {
            return ColorSpace{CGColorSpaceCreateDeviceRGB()};
        }

        [[nodiscard]] static auto deviceCMYK() noexcept
        {
            return ColorSpace{CGColorSpaceCreateDeviceCMYK()};
        }

        ColorSpace(const CGColorSpaceRef r) noexcept: ref{r} {}

        ~ColorSpace()
        {
            CGColorSpaceRelease(ref);
        }

        ColorSpace(ColorSpace&& other) noexcept:
            ref{other.ref}
        {
            other.ref = nullptr;
        }

        ColorSpace(const ColorSpace& other) noexcept:
            ref{other.ref}
        {
            CGColorSpaceRetain(ref);
        }

        ColorSpace& operator=(ColorSpace&& other) noexcept
        {
            if (&other == this) return *this;
            CGColorSpaceRelease(ref);
            ref = other.ref;
            other.ref = nullptr;
            return *this;
        }

        ColorSpace& operator=(const ColorSpace& other) noexcept
        {
            if (&other == this) return *this;
            CGColorSpaceRetain(other.ref);
            CGColorSpaceRelease(ref);
            ref = other.ref;
            return *this;
        }

        [[nodiscard]] operator CGColorSpaceRef() const noexcept
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
        CGColorSpaceRef ref = nullptr;
    };
}

#endif
