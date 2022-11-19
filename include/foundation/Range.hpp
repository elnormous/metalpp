#ifndef METALPP_FOUNDATION_RANGE_HPP
#define METALPP_FOUNDATION_RANGE_HPP

#include <objc/NSObjCRuntime.h>

namespace ns
{
    struct Range
    {
        Range() noexcept = default;
        Range(NSUInteger loc, NSUInteger len) noexcept: location{loc}, length{len} {}

        NSUInteger location = 0;
        NSUInteger length = 0;
    };
}

#endif
