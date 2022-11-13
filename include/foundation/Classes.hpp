#ifndef METALPP_FOUNDATION_CLASSES_HPP
#define METALPP_FOUNDATION_CLASSES_HPP

#include <objc/runtime.h>

namespace ns
{
    namespace cls
    {
        inline const auto autoreleasePool = objc_lookUpClass("NSAutoreleasePool");
        inline const auto array = objc_lookUpClass("NSArray");
        inline const auto dictionary = objc_lookUpClass("NSDictionary");
        inline const auto string = objc_lookUpClass("NSString");
    }
}

#endif
