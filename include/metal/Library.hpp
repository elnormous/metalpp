#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/String.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace mtl
{
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

        bool fastMathEnabled() const noexcept
        {
            return objc::sendMessage<BOOL>(*this, sel::fastMathEnabled) == YES;
        }

        void setFastMathEnabled(bool fastMathEnabled) const noexcept
        {
            objc::sendMessage(*this, sel::setFastMathEnabled_, static_cast<BOOL>(fastMathEnabled));
        }

        LanguageVersion languageVersion() const noexcept
        {
            return objc::sendMessage<LanguageVersion>(*this, sel::languageVersion);
        }

        void setLanguageVersion(LanguageVersion languageVersion) const noexcept
        {
            objc::sendMessage(*this, sel::setLanguageVersion_, languageVersion);
        }

        LibraryType libraryType() const noexcept
        {
            return objc::sendMessage<LibraryType>(*this, sel::libraryType);
        }

        void setFastMathEnabled(LibraryType libraryType) const noexcept
        {
            objc::sendMessage(*this, sel::setLibraryType_, static_cast<BOOL>(libraryType));
        }

        bool installName() const noexcept
        {
            const id installName = objc::sendMessage<id>(*this, sel::installName);
            return ns::String{objc::sendMessage<id>(installName, ns::sel::retain)};
        }

        void setInstallName(ns::String installName) const noexcept
        {
            objc::sendMessage(*this, sel::setInstallName_, static_cast<id>(installName));
        }

        bool preserveInvariance() const noexcept
        {
            return objc::sendMessage<BOOL>(*this, sel::preserveInvariance) == YES;
        }

        void setPreserveInstance(bool preserveInvariance) const noexcept
        {
            objc::sendMessage(*this, sel::setPreserveInvariance_, static_cast<BOOL>(preserveInvariance));
        }

        LibraryOptimizationLevel optimizationLevel() const noexcept
        {
            return objc::sendMessage<LibraryOptimizationLevel>(*this, sel::optimizationLevel);
        }

        void setOptimizationLevel(LibraryOptimizationLevel optimizationLevel) const noexcept
        {
            objc::sendMessage(*this, sel::setOptimizationLevel_, optimizationLevel);
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

        ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }

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
