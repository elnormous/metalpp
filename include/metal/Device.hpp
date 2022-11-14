#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <type_traits>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/Error.hpp"
#include "../foundation/String.hpp"
#include "DepthStencil.hpp"
#include "Library.hpp"
#include "Selectors.hpp"
#include "RenderPipeline.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

namespace mtl
{
    class Device final: public ns::Object
    {
    public:
        Device(): Object{MTLCreateSystemDefaultDevice()} {}

        Device(const id p) noexcept: Object{p} {}

        [[nodiscard]] ns::String name() const noexcept
        {
            const id name = objc::sendMessage<id>(*this, sel::name);
            return ns::String{objc::sendMessage<id>(name, ns::sel::retain)};
        }

        [[nodiscard]] DepthStencilState newDepthStencilStateWithDescriptor(const DepthStencilDescriptor& depthStencilDescriptor) const noexcept
        {
            const id depthStencilState = objc::sendMessage<id>(*this,
                                                               sel::newDepthStencilStateWithDescriptor_,
                                                               static_cast<id>(depthStencilDescriptor));

            return DepthStencilState{depthStencilState};
        }

        [[nodiscard]] Library newDefaultLibrary() const noexcept
        {
            const id library = objc::sendMessage<id>(*this, sel::newDefaultLibrary);
            return Library{library};
        }

        [[nodiscard]] Library newLibraryWithSource(const ns::String& source) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     sel::newLibraryWithSource_options_error_,
                                                     static_cast<id>(source),
                                                     nil,
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] Library newLibraryWithSource(const ns::String& source, const CompileOptions& compileOptions) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     sel::newLibraryWithSource_options_error_,
                                                     static_cast<id>(source),
                                                     static_cast<id>(compileOptions),
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return Library{library};
        }

        [[nodiscard]] RenderPipelineState newRenderPipelineStateWithDescriptor(const RenderPipelineDescriptor& renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = objc::sendMessage<id>(*this,
                                                                 sel::newRenderPipelineStateWithDescriptor_error_,
                                                                 static_cast<id>(renderPipelineDescriptor),
                                                                 &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, ns::sel::retain)};

            return RenderPipelineState{renderPipelineState};
        }
    };

    inline Device DepthStencilState::device()
    {
        id device = objc::sendMessage<id>(*this, sel::device);
        return Device{objc::sendMessage<id>(device, ns::sel::retain)};
    }
}

#endif
