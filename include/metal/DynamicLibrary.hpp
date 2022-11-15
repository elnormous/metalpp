#ifndef METALPP_METAL_DYNAMICLIBRARY_HPP
#define METALPP_METAL_DYNAMICLIBRARY_HPP

#include <os/availability.h>

namespace mtl
{
    class DynamicLibrary final: public ns::Object
    {
    public:
        Device device() const noexcept;
    } API_AVAILABLE(macos(11.0), ios(14.0));
}

#endif
