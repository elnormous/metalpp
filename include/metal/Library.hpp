#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"

namespace mtl
{
    class Function final: public ns::Object
    {
    public:
        Function(const id p) noexcept: Object{p} {}
    };
    
    class Library final: public ns::Object
    {
    public:
        Library(const id p) noexcept: Object{p} {}

        Function newFunctionWithName(const ns::String name) const noexcept
        {
            const id function = objc::sendMessage<id>(*this,
                                                      objc::newFunctionWithNameSel,
                                                      static_cast<id>(name));
            return Function{function};
        }
    };
}

#endif /* Library_h */
