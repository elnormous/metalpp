#ifndef METALPP_METAL_SELECTORS_HPP
#define METALPP_METAL_SELECTORS_HPP

namespace mtl
{
    namespace sel
    {
        inline const auto device = sel_registerName("device");
        inline const auto newCommandQueue = sel_registerName("newCommandQueue");
        inline const auto newCommandQueueWithMaxCommandBufferCount_ = sel_registerName("newCommandQueueWithMaxCommandBufferCount:");
        inline const auto newDepthStencilStateWithDescriptor_ = sel_registerName("newDepthStencilStateWithDescriptor:");
        inline const auto newTextureWithDescriptor_ = sel_registerName("newTextureWithDescriptor:");
        inline const auto newDefaultLibrary = sel_registerName("newDefaultLibrary");
        inline const auto newLibraryWithSource_options_error_ = sel_registerName("newLibraryWithSource:options:error:");
        inline const auto name = sel_registerName("name");
        inline const auto newRenderPipelineStateWithDescriptor_error_ = sel_registerName("newRenderPipelineStateWithDescriptor:error:");

        inline const auto newFunctionWithName_ = sel_registerName("newFunctionWithName:");

        inline const auto label = sel_registerName("label");
        inline const auto setLabel_ = sel_registerName("setLabel:");

        inline const auto vertexFunction = sel_registerName("vertexFunction");
        inline const auto setVertexFunction_ = sel_registerName("setVertexFunction:");
        inline const auto fragmentFunction = sel_registerName("fragmentFunction");
        inline const auto setFragmentFunction_ = sel_registerName("setFragmentFunction:");
        inline const auto vertexDescriptor = sel_registerName("vertexDescriptor");
        inline const auto setVertexDescriptor_ = sel_registerName("setVertexDescriptor:");
        inline const auto colorAttachments = sel_registerName("colorAttachments");
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

        inline const auto commandBuffer = sel_registerName("commandBuffer");
        inline const auto endEncoding = sel_registerName("endEncoding");
        inline const auto blitCommandEncoder = sel_registerName("blitCommandEncoder");
        inline const auto renderCommandEncoderWithDescriptor_ = sel_registerName("renderCommandEncoderWithDescriptor:");

        inline const auto cpuCacheMode = sel_registerName("cpuCacheMode");
        inline const auto setCpuCacheMode_ = sel_registerName("setCpuCacheMode:");
        inline const auto storageMode = sel_registerName("storageMode");
        inline const auto setStorageMode_ = sel_registerName("setStorageMode:");
        inline const auto hazardTrackingMode = sel_registerName("hazardTrackingMode");
        inline const auto setHazardTrackingMode_ = sel_registerName("setHazardTrackingMode:");
        inline const auto usage = sel_registerName("usage");
        inline const auto setUsage_ = sel_registerName("setUsage:");
        inline const auto allowGPUOptimizedContents = sel_registerName("allowGPUOptimizedContents");
        inline const auto setAllowGPUOptimizedContents_ = sel_registerName("setAllowGPUOptimizedContents:");
        inline const auto compressionType = sel_registerName("compressionType");
        inline const auto setCompressionType_ = sel_registerName("setCompressionType:");
        inline const auto swizzle = sel_registerName("swizzle");
        inline const auto setSwizzle_ = sel_registerName("setSwizzle:");

        inline const auto textureType = sel_registerName("textureType");
        inline const auto setTextureType_ = sel_registerName("setTextureType:");
        inline const auto pixelFormat = sel_registerName("pixelFormat");
        inline const auto setPixelFormat_ = sel_registerName("setPixelFormat:");
        inline const auto width = sel_registerName("width");
        inline const auto setWidth_ = sel_registerName("setWidth:");
        inline const auto height = sel_registerName("height");
        inline const auto setHeight_ = sel_registerName("setHeight:");
        inline const auto depth = sel_registerName("depth");
        inline const auto setDepth_ = sel_registerName("setDepth:");
        inline const auto mipmapLevelCount = sel_registerName("mipmapLevelCount");
        inline const auto setMipmapLevelCount_ = sel_registerName("setMipmapLevelCount:");
        inline const auto sampleCount = sel_registerName("sampleCount");
        inline const auto setSampleCount_ = sel_registerName("setSampleCount:");
        inline const auto arrayLength = sel_registerName("arrayLength");
        inline const auto setArrayLength_ = sel_registerName("setArrayLength:");

        inline const auto depthAttachment = sel_registerName("depthAttachment");
        inline const auto stencilAttachment = sel_registerName("stencilAttachment");
        inline const auto texture = sel_registerName("texture");
        inline const auto setTexture_ = sel_registerName("setTexture:");

        inline const auto level = sel_registerName("level");
        inline const auto setLevel_ = sel_registerName("setLevel:");
        inline const auto slice = sel_registerName("slice");
        inline const auto setSlice_ = sel_registerName("setSlice:");
        inline const auto depthPlane = sel_registerName("depthPlane");
        inline const auto setDepthPlane_ = sel_registerName("setDepthPlane:");
        inline const auto resolveTexture = sel_registerName("resolveTexture");
        inline const auto setResolveTexture_ = sel_registerName("setResolveTexture:");
        inline const auto resolveLevel = sel_registerName("resolveLevel");
        inline const auto setResolveLevel_ = sel_registerName("setResolveLevel:");
        inline const auto resolveSlice = sel_registerName("resolveSlice");
        inline const auto setResolveSlice_ = sel_registerName("setResolveSlice:");
        inline const auto resolveDepthPlane = sel_registerName("resolveDepthPlane");
        inline const auto setResolveDepthPlane_ = sel_registerName("setResolveDepthPlane:");
        inline const auto loadAction = sel_registerName("loadAction");
        inline const auto setLoadAction_ = sel_registerName("setLoadAction:");
        inline const auto storeAction = sel_registerName("storeAction");
        inline const auto setStoreAction_ = sel_registerName("setStoreAction:");
        inline const auto storeActionOptions = sel_registerName("storeActionOptions");
        inline const auto setStoreActionOptions_ = sel_registerName("setStoreActionOptions:");
        inline const auto clearColor = sel_registerName("clearColor");
        inline const auto setClearColor_ = sel_registerName("setClearColor:");
    }
}

#endif
