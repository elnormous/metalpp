#ifndef METALPP_OBJC_CLASSES_HPP
#define METALPP_OBJC_CLASSES_HPP

#include <objc/runtime.h>

namespace ns
{
    namespace cls
    {
        inline const auto object = objc_lookUpClass("NSObject");
    }
}

#endif
