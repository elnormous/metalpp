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
            const id name = objc::sendMessage<id>(*this, objc::nameSel);
            return ns::String{objc::sendMessage<id>(name, objc::retainSel)};
        }

        Library newDefaultLibrary() const
        {
            const id library = objc::sendMessage<id>(*this, objc::newDefaultLibrarySel);
            return Library{library};
        }

        Library newLibraryWithSource(const ns::String source) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     objc::newLibraryWithSource_options_error_Sel,
                                                     static_cast<id>(source),
                                                     nil,
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, objc::retainSel)};

            return Library{library};
        }

        RenderPipelineState newRenderPipelineStateWithDescriptor(const RenderPipelineDescriptor renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = objc::sendMessage<id>(*this,
                                                                 objc::newRenderPipelineStateWithDescriptor_error_Sel,
                                                                 static_cast<id>(renderPipelineDescriptor),
                                                                 &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, objc::retainSel)};

            return RenderPipelineState{renderPipelineState};
        }
    };
}



#endif
