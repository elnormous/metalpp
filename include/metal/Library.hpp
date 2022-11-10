#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include "../objc/Object.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class Function final: public ns::Object
    {
    public:
        using Object::Object;
    };
    
    class Library final: public ns::Object
    {
        inline static const auto newFunctionWithNameSel = sel_registerName("newFunctionWithName:");

    public:
        using Object::Object;

        Function newFunctionWithName(const ns::String name)
        {
            id function = objc::sendMessage<id>(*this,
                                                newFunctionWithNameSel,
                                                static_cast<id>(name));
            return Function{function};
        }
    };
}

#endif /* Library_h */
