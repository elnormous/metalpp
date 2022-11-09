#ifndef METALPP_METAL_METAL_HPP
#define METALPP_METAL_METAL_HPP

#include <string>
#include <type_traits>
#include "../objc/Object.hpp"
#include "Error.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

namespace metal
{
    class Device final: public objc::Object
    {
    public:
        Device():
            Object{MTLCreateSystemDefaultDevice()}
        {
            if (!*this)
                throw Error{"Failed to create Metal device"};
        }

        std::string getName() const
        {
            id name = objc::sendMessage<id>(*this, sel_registerName("name"));
            const char* str = objc::sendMessage<const char*, NSUInteger>(name, sel_registerName("cStringUsingEncoding:"), 1);
            return std::string{str};
        }
    };
}

#endif
