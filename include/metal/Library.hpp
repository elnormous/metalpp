#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include "../objc/Object.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class Function final: public ns::Object
    {
    public:
        Function(const id p) noexcept: Object{p}
        {
            if (p) objc::sendMessage(p, retainSel);
        }
    };
    
    class Library final: public ns::Object
    {
        inline static const auto newFunctionWithNameSel = sel_registerName("newFunctionWithName:");

    public:
        Library(const id p) noexcept: Object{p}
        {
            if (p) objc::sendMessage(p, retainSel);
        }

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
