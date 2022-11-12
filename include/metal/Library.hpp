#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace mtl
{
    enum class LibraryOptimizationLevel: NSInteger
    {
        Default = 0,
        Size = 1,
    };

    class CompileOptions final: public ns::Object
    {
    public:
        CompileOptions():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls::compileOptions, ns::sel::alloc), ns::sel::init)}
        {
        }
    };

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
                                                      sel::newFunctionWithName_,
                                                      static_cast<id>(name));
            return Function{function};
        }
    };
}

#endif /* Library_h */
