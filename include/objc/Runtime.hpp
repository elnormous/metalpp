#ifndef METALPP_OBJC_RUNTIME_HPP
#define METALPP_OBJC_RUNTIME_HPP

#include <objc/NSObjCRuntime.h>

namespace ns
{
    using Integer = NSInteger;
    using UInteger = NSUInteger;

    constexpr Integer IntegerMax = NSIntegerMax;
    constexpr Integer IntegerMin = NSIntegerMin;
    constexpr UInteger UIntegerMax = NSUIntegerMax;
}

#endif
