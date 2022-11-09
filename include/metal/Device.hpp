#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <type_traits>
#include "../objc/Object.hpp"
#include "../objc/String.hpp"
#include "Error.hpp"
#include "Library.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

namespace metal
{
    inline namespace detail
    {
        inline const auto newDefaultLibrarySel = sel_registerName("newDefaultLibrary");
        inline const auto nameSel = sel_registerName("name");
    }

    class Device final: public objc::Object
    {
    public:
        Device(): Object{MTLCreateSystemDefaultDevice()}
        {
            if (!*this)
                throw Error{"Failed to create Metal device"};
        }

        Library newDefaultLibrary() const
        {
            id library = objc::sendMessage<id>(*this, newDefaultLibrarySel);
            return Library{library};
        }

        objc::String getName() const
        {
            id name = objc::sendMessage<id>(*this, nameSel);
            return objc::String{name};
        }
    };
}



#endif
