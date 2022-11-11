#ifndef METALPP_METAL_DEVICE_HPP
#define METALPP_METAL_DEVICE_HPP

#include <type_traits>
#include "../objc/Object.hpp"
#include "../foundation/Error.hpp"
#include "../foundation/String.hpp"
#include "Library.hpp"
#include "RenderPipeline.hpp"

extern "C" id MTLCreateSystemDefaultDevice();

namespace mtl
{
    class Device final: public ns::Object
    {
        inline static const auto newDefaultLibrarySel = sel_registerName("newDefaultLibrary");
        inline static const auto newLibraryWithSourceOptionsErrorSel = sel_registerName("newLibraryWithSource:options:error:");
        inline static const auto nameSel = sel_registerName("name");
        inline static const auto newRenderPipelineStateWithDescriptorErrorSel = sel_registerName("newRenderPipelineStateWithDescriptor:error:");

    public:
        Device(): Object{MTLCreateSystemDefaultDevice()} {}

        ns::String name() const noexcept
        {
            const id name = objc::sendMessage<id>(*this, nameSel);
            return ns::String{objc::sendMessage<id>(name, retainSel)};
        }

        Library newDefaultLibrary() const
        {
            const id library = objc::sendMessage<id>(*this, newDefaultLibrarySel);
            return Library{library};
        }

        Library newLibraryWithSource(const ns::String source) const
        {
            id error;
            const id library = objc::sendMessage<id>(*this,
                                                     newLibraryWithSourceOptionsErrorSel,
                                                     static_cast<id>(source),
                                                     nil,
                                                     &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, retainSel)};

            return Library{library};
        }

        RenderPipelineState newRenderPipelineStateWithDescriptor(const RenderPipelineDescriptor renderPipelineDescriptor) const
        {
            id error;
            const id renderPipelineState = objc::sendMessage<id>(*this, newRenderPipelineStateWithDescriptorErrorSel,
                                                                 static_cast<id>(renderPipelineDescriptor),
                                                                 &error);

            if (error != nil)
                throw ns::Error{objc::sendMessage<id>(error, retainSel)};

            return RenderPipelineState{renderPipelineState};
        }
    };
}



#endif
