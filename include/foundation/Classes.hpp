#ifndef METALPP_FOUNDATION_CLASSES_HPP
#define METALPP_FOUNDATION_CLASSES_HPP

#include <objc/runtime.h>

namespace ns
{
    namespace cls
    {
        inline const auto string = objc_lookUpClass("NSString");
        inline const auto autoreleasePool = objc_lookUpClass("NSAutoreleasePool");
    }
}

#endif