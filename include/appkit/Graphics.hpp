#ifndef METALPP_APPKIT_GRAPHICS_HPP
#define METALPP_APPKIT_GRAPHICS_HPP

#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"

namespace ns
{
    enum class BackingStoreType: UInteger
    {
        /* Retained and Nonretained have effectively been synonyms of Buffered since OS X Mountain Lion.  Please switch to the equivalent Buffered.
         */
        Retained API_DEPRECATED_WITH_REPLACEMENT("Buffered", macos(10.0,10.13)) = 0,
        Nonretained API_DEPRECATED_WITH_REPLACEMENT("Buffered", macos(10.0,10.13)) = 1,
        Buffered = 2,
    };

    enum class WindowOrderingMode: Integer
    {
        Above         =  1,
        Below         = -1,
        Out           =  0
    };
}

#endif
