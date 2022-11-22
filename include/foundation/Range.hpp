#ifndef METALPP_FOUNDATION_RANGE_HPP
#define METALPP_FOUNDATION_RANGE_HPP

#include "../objc/Runtime.hpp"

namespace ns
{
    struct Range
    {
        Range() noexcept = default;
        Range(UInteger loc, UInteger len) noexcept: location{loc}, length{len} {}

        UInteger location = 0;
        UInteger length = 0;
    };
}

#endif
