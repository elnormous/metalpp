#ifndef METALPP_METAL_ERROR_HPP
#define METALPP_METAL_ERROR_HPP

#include <stdexcept>

namespace metal
{
    class Error final: public std::runtime_error
    {
    public:
        using std::runtime_error::runtime_error;
    };
}

#endif
