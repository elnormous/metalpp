#ifndef METALPP_OBJC_SELECTORS_HPP
#define METALPP_OBJC_SELECTORS_HPP

#include <objc/message.h>

namespace ns
{
    namespace sel
    {
        inline const auto alloc = sel_registerName("alloc");
        inline const auto init = sel_registerName("init");
        inline const auto retain = sel_registerName("retain");
        inline const auto release = sel_registerName("release");
        inline const auto retainCount = sel_registerName("retainCount");
    }
}

#endif
