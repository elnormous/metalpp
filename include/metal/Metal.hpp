#ifndef METALPP_METAL_METAL_HPP
#define METALPP_METAL_METAL_HPP

#include <type_traits>
#include "../objc/Object.hpp"
#include "../objc/String.hpp"
#include "Error.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

namespace metal
{
    namespace detail
    {
        
    }

    class Device;
    class Library;

    class Function final: public objc::Object
    {
        friend Library;
    protected:
        Function(id function): Object{function} {}

    public:
    };

    class Library final: public objc::Object
    {
        friend Device;
    protected:
        Library(id library): Object{library} {}

    public:
        Function newFunctionWithName(const objc::String name)
        {
            id function = objc::sendMessage<id>(*this,
                                                sel_registerName("newFunctionWithName:"),
                                                static_cast<id>(name));
            return Function{function};
        }
    };

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
            id library = objc::sendMessage<id>(*this, sel_registerName("newDefaultLibrary"));
            return Library{library};
        }

        objc::String getName() const
        {
            id name = objc::sendMessage<id>(*this, sel_registerName("name"));
            return objc::String{name};
        }
    };
}

#endif
