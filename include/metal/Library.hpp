#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include "../objc/Object.hpp"
#include "../foundation/String.hpp"

namespace metal
{
    inline namespace detail
    {
        inline const auto newFunctionWithNameSel = sel_registerName("newFunctionWithName:");
    }
    
    class Function final: public objc::Object
    {
    public:
        Function(id p): Object{p} {}
    };
    
    class Library final: public objc::Object
    {
    public:
        Library(id p): Object{p} {}

        Function newFunctionWithName(const foundation::String name)
        {
            id function = objc::sendMessage<id>(*this,
                                                newFunctionWithNameSel,
                                                static_cast<id>(name));
            return Function{function};
        }
    };
}

#endif /* Library_h */
