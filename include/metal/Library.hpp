#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/Array.hpp"
#include "../foundation/Dictionary.hpp"
#include "../foundation/String.hpp"
#include "DynamicLibrary.hpp"
#include "Selectors.hpp"

namespace mtl
{
    class Device;

    enum class LanguageVersion: NSUInteger
    {
        Version1_0 API_DEPRECATED("Use a newer language standard", ios(9.0, 16.0)) API_UNAVAILABLE(macos, macCatalyst) = (1 << 16),
        Version1_1 API_AVAILABLE(macos(10.11), ios(9.0)) = (1 << 16) + 1,
        Version1_2 API_AVAILABLE(macos(10.12), ios(10.0)) = (1 << 16) + 2,
        Version2_0 API_AVAILABLE(macos(10.13), ios(11.0)) = (2 << 16),
        Version2_1 API_AVAILABLE(macos(10.14), ios(12.0)) = (2 << 16) + 1,
        Version2_2 API_AVAILABLE(macos(10.15), ios(13.0)) = (2 << 16) + 2,
        Version2_3 API_AVAILABLE(macos(11.0), ios(14.0)) = (2 << 16) + 3,
        Version2_4 API_AVAILABLE(macos(12.0), ios(15.0)) = (2 << 16) + 4,
        Version3_0 API_AVAILABLE(macos(13.0), ios(16.0)) = (3 << 16) + 0,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class LibraryType: NSInteger
    {
        Executable = 0,
        Dynamic = 1,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    enum class LibraryOptimizationLevel: NSInteger
    {
        Default = 0,
        Size = 1,
    } API_AVAILABLE(macos(13.0), ios(16.0));

    class CompileOptions final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLCompileOptions");
    public:
        CompileOptions():
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] ns::Dictionary<ns::String, ns::Object> preprocessorMacros() const noexcept
        {
            return getObject<ns::Dictionary<ns::String, ns::Object>>(sel::preprocessorMacros);
        }

        void setPreprocessorMacros(const ns::Dictionary<ns::String, ns::Object>& preprocessorMacros) noexcept
        {
            sendMessage(sel::setPreprocessorMacros_, static_cast<id>(preprocessorMacros));
        }

        [[nodiscard]] bool fastMathEnabled() const noexcept
        {
            return sendMessage<BOOL>(sel::fastMathEnabled) == YES;
        }

        void setFastMathEnabled(bool fastMathEnabled) noexcept
        {
            sendMessage(sel::setFastMathEnabled_, fastMathEnabled ? YES : NO);
        }

        [[nodiscard]] LanguageVersion languageVersion() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<LanguageVersion>(sel::languageVersion);
        }

        void setLanguageVersion(LanguageVersion languageVersion) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(sel::setLanguageVersion_, languageVersion);
        }

        [[nodiscard]] LibraryType libraryType() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<LibraryType>(sel::libraryType);
        }

        void setLibraryType(LibraryType libraryType) noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            sendMessage(sel::setLibraryType_, libraryType);
        }

        [[nodiscard]] ns::String installName() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return getObject<ns::String>(sel::installName);
        }

        void setInstallName(ns::String installName) noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            sendMessage(sel::setInstallName_, static_cast<id>(installName));
        }

        [[nodiscard]] ns::Array<DynamicLibrary> libraries() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return getObject<ns::Array<DynamicLibrary>>(sel::libraries);
        }

        void setLibraries(const ns::Array<DynamicLibrary>& libraries) noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            sendMessage(sel::setLibraries_, static_cast<id>(libraries));
        }

        [[nodiscard]] bool preserveInvariance() const noexcept API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(14.0))
        {
            return sendMessage<BOOL>(sel::preserveInvariance) == YES;
        }

        void setPreserveInstance(bool preserveInvariance) noexcept API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(14.0))
        {
            sendMessage(sel::setPreserveInvariance_, preserveInvariance ? YES : NO);
        }

        [[nodiscard]] LibraryOptimizationLevel optimizationLevel() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<LibraryOptimizationLevel>(sel::optimizationLevel);
        }

        void setOptimizationLevel(LibraryOptimizationLevel optimizationLevel) noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            sendMessage(sel::setOptimizationLevel_, optimizationLevel);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class Function final: public ns::Object
    {
    public:
        Function() = delete;

        Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            return getObject<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            sendMessage(sel::setLabel_, static_cast<id>(label));
        }
    };
    
    class Library final: public ns::Object
    {
    public:
        Library() = delete;

        Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            return getObject<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] Function newFunction(const ns::String& name) const noexcept
        {
            const id function = sendMessage<id>(sel::newFunctionWithName_,
                                                static_cast<id>(name));
            return Function{function};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
