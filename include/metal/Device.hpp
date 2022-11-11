#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <type_traits>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/Error.hpp"
#include "../foundation/String.hpp"
#include "Library.hpp"
#include "RenderPipeline.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

namespace mtl
{
    class Device final: public ns::Object
    {
    public:
        Device(): Object{MTLCreateSystemDefaultDevice()} {}

        ns::String name() const noexcept
        {
            const id name = objc::sendMessage<id>(*this, objc::sel::name);
            return ns::String{objc::sendMessage<id>(name, objc::sel::retain)};
        }

        Library newDefaultLibrary() const
        {
            const id library = objc::sendMessage<id>(*this, objc::sel::newDefaultLibrary);
            return Library{library};
        }

        Library newLibraryWithSource(const ns::String source) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     objc::sel::newLibraryWithSource_options_error_,
                                                     static_cast<id>(source),
                                                     nil,
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, objc::sel::retain)};

            return Library{library};
        }

        RenderPipelineState newRenderPipelineStateWithDescriptor(const RenderPipelineDescriptor renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = objc::sendMessage<id>(*this,
                                                                 objc::sel::newRenderPipelineStateWithDescriptor_error_,
                                                                 static_cast<id>(renderPipelineDescriptor),
                                                                 &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, objc::sel::retain)};

            return RenderPipelineState{renderPipelineState};
        }
    };
}



#endif
