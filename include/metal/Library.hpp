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

    enum class LanguageVersion: NSUInteger
    {
        Version1_0 = (1 << 16),
        Version1_1 = (1 << 16) + 1,
        Version1_2 = (1 << 16) + 2,
        Version2_0 = (2 << 16),
        Version2_1 = (2 << 16) + 1,
        Version2_2 = (2 << 16) + 2,
        Version2_3 = (2 << 16) + 3,
        Version2_4 = (2 << 16) + 4,
        Version3_0 = (3 << 16) + 0,
    };

    enum class LibraryType: NSInteger
    {
        Executable = 0,
        Dynamic = 1,
    };

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
