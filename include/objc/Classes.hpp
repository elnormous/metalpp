#ifndef METALPP_OBJC_CLASSES_HPP
#define METALPP_OBJC_CLASSES_HPP

#include <objc/runtime.h>

namespace objc
{
    inline namespace detail
    {
        inline const auto objectClass = objc_lookUpClass("NSObject");
        inline const auto stringClass = objc_lookUpClass("NSString");
        inline const auto autoreleasePoolClass = objc_lookUpClass("NSAutoreleasePool");

        inline const auto depthStencilDescriptorClass = objc_lookUpClass("MTLDepthStencilDescriptor");
        inline const auto renderPipelineDescriptorClass = objc_lookUpClass("MTLRenderPipelineDescriptor");
        inline const auto vertexDescriptorClass = objc_lookUpClass("MTLVertexDescriptor");
    }
}

#endif
