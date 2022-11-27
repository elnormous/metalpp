#ifndef METALPP_METAL_SELECTORS_HPP
#define METALPP_METAL_SELECTORS_HPP

namespace mtl
{
    namespace sel
    {
        inline const auto device = sel_registerName("device");
        inline const auto setDevice_ = sel_registerName("setDevice:");

        inline const auto name = sel_registerName("name");
        inline const auto location = sel_registerName("location");
        inline const auto locationNumber = sel_registerName("locationNumber");
        inline const auto currentAllocatedSize = sel_registerName("currentAllocatedSize");
        inline const auto newCommandQueue = sel_registerName("newCommandQueue");
        inline const auto newCommandQueueWithMaxCommandBufferCount_ = sel_registerName("newCommandQueueWithMaxCommandBufferCount:");
        inline const auto newDepthStencilStateWithDescriptor_ = sel_registerName("newDepthStencilStateWithDescriptor:");
        inline const auto newBufferWithLength_options_ = sel_registerName("newBufferWithLength:options:");
        inline const auto newBufferWithBytes_length_options_ = sel_registerName("newBufferWithBytes:length:options:");
        inline const auto newTextureWithDescriptor_ = sel_registerName("newTextureWithDescriptor:");
        inline const auto newSamplerStateWithDescriptor_ = sel_registerName("newSamplerStateWithDescriptor:");
        inline const auto newDefaultLibrary = sel_registerName("newDefaultLibrary");
        inline const auto newLibraryWithSource_options_error_ = sel_registerName("newLibraryWithSource:options:error:");
        inline const auto supportsFeatureSet_ = sel_registerName("supportsFeatureSet:");
        inline const auto supportsFamily_ = sel_registerName("supportsFamily:");
        inline const auto newRenderPipelineStateWithDescriptor_error_ = sel_registerName("newRenderPipelineStateWithDescriptor:error:");
        inline const auto newFunctionWithName_ = sel_registerName("newFunctionWithName:");

        inline const auto label = sel_registerName("label");
        inline const auto setLabel_ = sel_registerName("setLabel:");

        inline const auto contents = sel_registerName("contents");
        inline const auto didModifyRange_ = sel_registerName("didModifyRange:");
        inline const auto gpuAddress = sel_registerName("gpuAddress");

        inline const auto isBlendingEnabled = sel_registerName("isBlendingEnabled");
        inline const auto setBlendingEnabled_ = sel_registerName("setBlendingEnabled:");
        inline const auto sourceRGBBlendFactor = sel_registerName("sourceRGBBlendFactor");
        inline const auto setSourceRGBBlendFactor_ = sel_registerName("setSourceRGBBlendFactor:");
        inline const auto destinationRGBBlendFactor = sel_registerName("destinationRGBBlendFactor");
        inline const auto setDestinationRGBBlendFactor_ = sel_registerName("setDestinationRGBBlendFactor:");
        inline const auto rgbBlendOperation = sel_registerName("rgbBlendOperation");
        inline const auto setRgbBlendOperation_ = sel_registerName("setRgbBlendOperation:");
        inline const auto sourceAlphaBlendFactor = sel_registerName("sourceAlphaBlendFactor");
        inline const auto setSourceAlphaBlendFactor_ = sel_registerName("setSourceAlphaBlendFactor:");
        inline const auto destinationAlphaBlendFactor = sel_registerName("destinationAlphaBlendFactor");
        inline const auto setDestinationAlphaBlendFactor_ = sel_registerName("setDestinationAlphaBlendFactor:");
        inline const auto alphaBlendOperation = sel_registerName("alphaBlendOperation");
        inline const auto setAlphaBlendOperation_ = sel_registerName("setAlphaBlendOperation:");
        inline const auto writeMask = sel_registerName("writeMask");
        inline const auto setWriteMask_ = sel_registerName("setWriteMask:");

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
        inline const auto functionType = sel_registerName("functionType");
        inline const auto patchType = sel_registerName("patchType");
        inline const auto patchControlPointCount = sel_registerName("patchControlPointCount");
        inline const auto vertexAttributes = sel_registerName("vertexAttributes");
        inline const auto stageInputAttributes = sel_registerName("stageInputAttributes");
        inline const auto functionConstantsDictionary = sel_registerName("functionConstantsDictionary");

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
        inline const auto presentDrawable_ = sel_registerName("presentDrawable:");
        inline const auto presentDrawable_atTime_ = sel_registerName("presentDrawable:atTime:");
        inline const auto commit = sel_registerName("commit");
        inline const auto waitUntilCompleted = sel_registerName("waitUntilCompleted");

        inline const auto cpuCacheMode = sel_registerName("cpuCacheMode");
        inline const auto setCpuCacheMode_ = sel_registerName("setCpuCacheMode:");
        inline const auto storageMode = sel_registerName("storageMode");
        inline const auto setStorageMode_ = sel_registerName("setStorageMode:");
        inline const auto hazardTrackingMode = sel_registerName("hazardTrackingMode");
        inline const auto setHazardTrackingMode_ = sel_registerName("setHazardTrackingMode:");
        inline const auto resourceOptions = sel_registerName("resourceOptions");
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
        inline const auto clearDepth = sel_registerName("clearDepth");
        inline const auto setClearDepth_ = sel_registerName("setClearDepth:");
        inline const auto depthResolveFilter = sel_registerName("depthResolveFilter");
        inline const auto setDepthResolveFilter_ = sel_registerName("setDepthResolveFilter:");
        inline const auto clearStencil = sel_registerName("clearStencil");
        inline const auto setClearStencil_ = sel_registerName("setClearStencil:");
        inline const auto stencilResolveFilter = sel_registerName("stencilResolveFilter");
        inline const auto setStencilResolveFilter_ = sel_registerName("setStencilResolveFilter:");

        inline const auto setRenderPipelineState_ = sel_registerName("setRenderPipelineState:");
        inline const auto setVertexBuffer_offset_atIndex_ = sel_registerName("setVertexBuffer:offset:atIndex:");
        inline const auto setFragmentBuffer_offset_atIndex_ = sel_registerName("setFragmentBuffer:offset:atIndex:");
        inline const auto setFragmentTexture_atIndex_ = sel_registerName("setFragmentTexture:atIndex:");
        inline const auto setFragmentSamplerState_atIndex_ = sel_registerName("setFragmentSamplerState:atIndex:");
        inline const auto drawPrimitives_vertexStart_vertexCount_ = sel_registerName("drawPrimitives:vertexStart:vertexCount:");
        inline const auto drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_ = sel_registerName("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:");

        inline const auto minFilter = sel_registerName("minFilter");
        inline const auto setMinFilter_ = sel_registerName("setMinFilter:");
        inline const auto magFilter = sel_registerName("magFilter");
        inline const auto setMagFilter_ = sel_registerName("setMagFilter:");
        inline const auto mipFilter = sel_registerName("mipFilter");
        inline const auto setMipFilter_ = sel_registerName("setMipFilter:");
        inline const auto maxAnisotropy = sel_registerName("maxAnisotropy");
        inline const auto setMaxAnisotropy_ = sel_registerName("setMaxAnisotropy:");
        inline const auto sAddressMode = sel_registerName("sAddressMode");
        inline const auto setSAddressMode_ = sel_registerName("setSAddressMode:");
        inline const auto tAddressMode = sel_registerName("tAddressMode");
        inline const auto setTAddressMode_ = sel_registerName("setTAddressMode:");
        inline const auto rAddressMode = sel_registerName("rAddressMode");
        inline const auto setRAddressMode_ = sel_registerName("setRAddressMode:");
        inline const auto borderColor = sel_registerName("borderColor");
        inline const auto setBorderColor_ = sel_registerName("setBorderColor:");
        inline const auto normalizedCoordinates = sel_registerName("normalizedCoordinates");
        inline const auto setNormalizedCoordinates_ = sel_registerName("setNormalizedCoordinates:");
        inline const auto lodMinClamp = sel_registerName("lodMinClamp");
        inline const auto setLodMinClamp_ = sel_registerName("setLodMinClamp:");
        inline const auto lodMaxClamp = sel_registerName("lodMaxClamp");
        inline const auto setLodMaxClamp_ = sel_registerName("setLodMaxClamp:");
        inline const auto lodAverage = sel_registerName("lodAverage");
        inline const auto setLodAverage_ = sel_registerName("setLodAverage:");
        inline const auto compareFunction = sel_registerName("compareFunction");
        inline const auto setCompareFunction_ = sel_registerName("setCompareFunction:");
        inline const auto supportArgumentBuffers = sel_registerName("supportArgumentBuffers");
        inline const auto setSupportArgumentBuffers_ = sel_registerName("setSupportArgumentBuffers:");
    }
}

#endif
