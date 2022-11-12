#ifndef METALPP_METAL_CLASSES_HPP
#define METALPP_METAL_CLASSES_HPP

#include <objc/runtime.h>

namespace mtl
{
    namespace cls
    {
        inline const auto compileOptions = objc_lookUpClass("MTLCompileOptions");
        inline const auto depthStencilDescriptor = objc_lookUpClass("MTLDepthStencilDescriptor");
        inline const auto renderPipelineDescriptor = objc_lookUpClass("MTLRenderPipelineDescriptor");
        inline const auto vertexDescriptor = objc_lookUpClass("MTLVertexDescriptor");
    }
}

#endif
