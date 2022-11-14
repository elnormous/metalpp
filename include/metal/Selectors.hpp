#ifndef METALPP_METAL_SELECTORS_HPP
#define METALPP_METAL_SELECTORS_HPP

namespace mtl
{
    namespace sel
    {
        inline const auto device = sel_registerName("device");
        inline const auto newCommandQueue = sel_registerName("newCommandQueue");
        inline const auto newDepthStencilStateWithDescriptor_ = sel_registerName("newDepthStencilStateWithDescriptor:");
        inline const auto newDefaultLibrary = sel_registerName("newDefaultLibrary");
        inline const auto newLibraryWithSource_options_error_ = sel_registerName("newLibraryWithSource:options:error:");
        inline const auto name = sel_registerName("name");
        inline const auto newRenderPipelineStateWithDescriptor_error_ = sel_registerName("newRenderPipelineStateWithDescriptor:error:");

        inline const auto newFunctionWithName_ = sel_registerName("newFunctionWithName:");

        inline const auto label = sel_registerName("label");
        inline const auto setLabel_ = sel_registerName("setLabel:");

        inline const auto vertexFunction = sel_registerName("setVertexFunction");
        inline const auto setVertexFunction_ = sel_registerName("setVertexFunction:");
        inline const auto fragmentFunction = sel_registerName("fragmentFunction");
        inline const auto setFragmentFunction_ = sel_registerName("setFragmentFunction:");
        inline const auto vertexDescriptor = sel_registerName("vertexDescriptor");
        inline const auto setVertexDescriptor_ = sel_registerName("setVertexDescriptor:");
        inline const auto depthAttachmentPixelFormat = sel_registerName("depthAttachmentPixelFormat");
        inline const auto setDepthAttachmentPixelFormat_ = sel_registerName("setDepthAttachmentPixelFormat:");
        inline const auto stencilAttachmentPixelFormat = sel_registerName("stencilAttachmentPixelFormat");
        inline const auto setStencilAttachmentPixelFormat_ = sel_registerName("setStencilAttachmentPixelFormat:");

        inline const auto layouts = sel_registerName("layouts");
        inline const auto attributes = sel_registerName("attributes");
        inline const auto reset = sel_registerName("reset");

        inline const auto format = sel_registerName("format");
        inline const auto setFormat_ = sel_registerName("setFormat:");
        inline const auto offset = sel_registerName("offset");
        inline const auto setOffset_ = sel_registerName("setOffset:");
        inline const auto bufferIndex = sel_registerName("bufferIndex");
        inline const auto setBufferIndex_ = sel_registerName("setBufferIndex:");

        inline const auto stride = sel_registerName("stride");
        inline const auto setStride_ = sel_registerName("setStride:");
        inline const auto stepFunction = sel_registerName("stepFunction");
        inline const auto setStepFunction_ = sel_registerName("setStepFunction:");
        inline const auto stepRate = sel_registerName("stepRate");
        inline const auto setStepRate_ = sel_registerName("setStepRate:");
        inline const auto preprocessorMacros = sel_registerName("preprocessorMacros");
        inline const auto setPreprocessorMacros_ = sel_registerName("setPreprocessorMacros:");
        inline const auto fastMathEnabled = sel_registerName("fastMathEnabled");
        inline const auto setFastMathEnabled_ = sel_registerName("setFastMathEnabled:");
        inline const auto languageVersion = sel_registerName("languageVersion");
        inline const auto setLanguageVersion_ = sel_registerName("setLanguageVersion:");
        inline const auto libraryType = sel_registerName("libraryType");
        inline const auto setLibraryType_ = sel_registerName("setLibraryType:");
        inline const auto installName = sel_registerName("installName");
        inline const auto setInstallName_ = sel_registerName("setInstallName:");
        inline const auto libraries = sel_registerName("libraries");
        inline const auto setLibraries_ = sel_registerName("setLibraries:");
        inline const auto preserveInvariance = sel_registerName("preserveInvariance");
        inline const auto setPreserveInvariance_ = sel_registerName("setPreserveInvariance:");
        inline const auto optimizationLevel = sel_registerName("optimizationLevel");
        inline const auto setOptimizationLevel_ = sel_registerName("setOptimizationLevel:");

    }
}

#endif
