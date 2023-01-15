#ifndef METALPP_METAL_LIBRARY_HPP
#define METALPP_METAL_LIBRARY_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Array.hpp"
#include "../foundation/Dictionary.hpp"
#include "../foundation/Error.hpp"
#include "../foundation/String.hpp"
#include "DynamicLibrary.hpp"
#include "FunctionConstantValues.hpp"

namespace mtl
{
    class Device;

    enum class PatchType: ns::UInteger
    {
        None = 0,
        Triangle = 1,
        Quad = 2,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    class VertexAttribute final: public ns::Object
    {
    public:
        VertexAttribute() = delete;

        // not implemented
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class Attribute final: public ns::Object
    {
    public:
        Attribute() = delete;

        // not implemented
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class FunctionType: ns::UInteger
    {
        Vertex = 1,
        Fragment = 2,
        Kernel = 3,
        Visible API_AVAILABLE(macos(11.0), ios(14.0)) = 5,
        Intersection API_AVAILABLE(macos(11.0), ios(14.0)) = 6,
        Mesh API_AVAILABLE(macos(13.0), ios(16.0)) = 7,
        Object API_AVAILABLE(macos(13.0), ios(16.0)) = 8,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class FunctionConstant final: public ns::Object
    {
    public:
        FunctionConstant() = delete;

        // not implemented
    };

    class Function final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(functionType, "functionType");
        METALPP_PRIVATE_SEL(patchType, "patchType");
        METALPP_PRIVATE_SEL(patchControlPointCount, "patchControlPointCount");
        METALPP_PRIVATE_SEL(vertexAttributes, "vertexAttributes");
        METALPP_PRIVATE_SEL(stageInputAttributes, "stageInputAttributes");
        METALPP_PRIVATE_SEL(name, "name");
        METALPP_PRIVATE_SEL(functionConstantsDictionary, "functionConstantsDictionary");

        using Object::Object;
        using Object::operator=;
        
        Function() = delete;

        [[nodiscard]] auto label() const noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto functionType() const noexcept
        {
            return sendMessage<FunctionType>(METALPP_SEL(functionType));
        }

        [[nodiscard]] auto patchType() const noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            return sendMessage<PatchType>(METALPP_SEL(patchType));
        }

        [[nodiscard]] auto patchControlPointCount() const noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            return sendMessage<ns::Integer>(METALPP_SEL(patchControlPointCount));
        }

        [[nodiscard]] auto vertexAttributes() const noexcept
        {
            return ns::Array<VertexAttribute>{sendMessage<id>(METALPP_SEL(vertexAttributes))};
        }

        [[nodiscard]] auto stageInputAttributes() const noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            return ns::Array<Attribute>{sendMessage<id>(METALPP_SEL(stageInputAttributes))};
        }

        [[nodiscard]] auto name() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(name))};
        }

        [[nodiscard]] auto functionConstantsDictionary() const noexcept API_AVAILABLE(macos(10.12), ios(10.0))
        {
            return ns::Dictionary<ns::String, FunctionConstant>{sendMessage<id>(METALPP_SEL(functionConstantsDictionary))};
        }
    };

    enum class LanguageVersion: ns::UInteger
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

    enum class LibraryType: ns::Integer
    {
        Executable = 0,
        Dynamic = 1,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    enum class LibraryOptimizationLevel: ns::Integer
    {
        Default = 0,
        Size = 1,
    } API_AVAILABLE(macos(13.0), ios(16.0));

    class CompileOptions final: public ns::Object
    {
    public:
        static constexpr bool copying = true;

        METALPP_PRIVATE_CLS("MTLCompileOptions");

        METALPP_PRIVATE_SEL(preprocessorMacros, "preprocessorMacros");
        METALPP_PRIVATE_SEL(setPreprocessorMacros_, "setPreprocessorMacros:");
        METALPP_PRIVATE_SEL(fastMathEnabled, "fastMathEnabled");
        METALPP_PRIVATE_SEL(setFastMathEnabled_, "setFastMathEnabled:");
        METALPP_PRIVATE_SEL(languageVersion, "languageVersion");
        METALPP_PRIVATE_SEL(setLanguageVersion_, "setLanguageVersion:");
        METALPP_PRIVATE_SEL(libraryType, "libraryType");
        METALPP_PRIVATE_SEL(setLibraryType_, "setLibraryType:");
        METALPP_PRIVATE_SEL(installName, "installName");
        METALPP_PRIVATE_SEL(setInstallName_, "setInstallName:");
        METALPP_PRIVATE_SEL(libraries, "libraries");
        METALPP_PRIVATE_SEL(setLibraries_, "setLibraries:");
        METALPP_PRIVATE_SEL(preserveInvariance, "preserveInvariance");
        METALPP_PRIVATE_SEL(setPreserveInvariance_, "setPreserveInvariance:");
        METALPP_PRIVATE_SEL(optimizationLevel, "optimizationLevel");
        METALPP_PRIVATE_SEL(setOptimizationLevel_, "setOptimizationLevel:");

        using Object::Object;
        using Object::operator=;

        CompileOptions() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto preprocessorMacros() const noexcept
        {
            return ns::Dictionary<ns::String, ns::Object>{sendMessage<id>(METALPP_SEL(preprocessorMacros))};
        }

        void setPreprocessorMacros(const ns::Dictionary<ns::String, ns::Object>& preprocessorMacros) noexcept
        {
            sendMessage(METALPP_SEL(setPreprocessorMacros_), preprocessorMacros.get());
        }

        [[nodiscard]] auto fastMathEnabled() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(fastMathEnabled)) == YES;
        }

        void setFastMathEnabled(const bool fastMathEnabled) noexcept
        {
            sendMessage(METALPP_SEL(setFastMathEnabled_), fastMathEnabled ? YES : NO);
        }

        [[nodiscard]] auto languageVersion() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<LanguageVersion>(METALPP_SEL(languageVersion));
        }

        void setLanguageVersion(const LanguageVersion languageVersion) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(METALPP_SEL(setLanguageVersion_), languageVersion);
        }

        [[nodiscard]] auto libraryType() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return sendMessage<LibraryType>(METALPP_SEL(libraryType));
        }

        void setLibraryType(const LibraryType libraryType) noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            sendMessage(METALPP_SEL(setLibraryType_), libraryType);
        }

        [[nodiscard]] auto installName() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return ns::String{sendMessage<id>(METALPP_SEL(installName))};
        }

        void setInstallName(const ns::String& installName) noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            sendMessage(METALPP_SEL(setInstallName_), installName.get());
        }

        [[nodiscard]] auto libraries() const noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            return ns::Array<DynamicLibrary>{sendMessage<id>(METALPP_SEL(libraries))};
        }

        void setLibraries(const ns::Array<DynamicLibrary>& libraries) noexcept API_AVAILABLE(macos(11.0), ios(14.0))
        {
            sendMessage(METALPP_SEL(setLibraries_), libraries.get());
        }

        [[nodiscard]] auto preserveInvariance() const noexcept API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(14.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(preserveInvariance)) == YES;
        }

        void setPreserveInstance(const bool preserveInvariance) noexcept API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(14.0))
        {
            sendMessage(METALPP_SEL(setPreserveInvariance_), preserveInvariance ? YES : NO);
        }

        [[nodiscard]] auto optimizationLevel() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<LibraryOptimizationLevel>(METALPP_SEL(optimizationLevel));
        }

        void setOptimizationLevel(const LibraryOptimizationLevel optimizationLevel) noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            sendMessage(METALPP_SEL(setOptimizationLevel_), optimizationLevel);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
    
    class Library final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(device, "device");
        METALPP_PRIVATE_SEL(newFunctionWithName_, "newFunctionWithName:");
        METALPP_PRIVATE_SEL(newFunctionWithName_constantValues_error_, "newFunctionWithName:constantValues:error:");

        using Object::Object;
        using Object::operator=;

        Library() = delete;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] auto newFunction(const ns::String& name) const noexcept
        {
            const id function = sendMessage<id>(METALPP_SEL(newFunctionWithName_),
                                                name.get());
            return Function{function, ns::adopt};
        }

        [[nodiscard]] auto newFunction(const ns::String& name, const FunctionConstantValues& constantValues) const API_AVAILABLE(macos(10.12), ios(10.0))
        {
            id error = nil;

            const id function = sendMessage<id>(METALPP_SEL(newFunctionWithName_constantValues_error_),
                                                name.get(),
                                                constantValues.get(),
                                                &error);

            if (error != nil)
                throw ns::Error{error};

            return Function{function, ns::adopt};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
