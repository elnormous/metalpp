#ifndef METALPP_METAL_DRAWABLE_HPP
#define METALPP_METAL_DRAWABLE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"

namespace mtl
{
    class Drawable final: public ns::Object
    {
    public:
        Drawable() = delete;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
