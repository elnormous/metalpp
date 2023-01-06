#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "metal/Metal.hpp"

TEST_CASE("Device")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    REQUIRE(device);
    CHECK(device.supportsFeatureSet(FeatureSet::macOS_GPUFamily1_v1));
    CHECK(device.supportsFamily(GPUFamily::Common1));

    const ns::String name = device.name();
    REQUIRE(name);
    CHECK(name.retainCount());
    CHECK(name.length());

    CHECK(device.currentAllocatedSize() == 0);

    CHECK(device.location() != DeviceLocation::Unspecified);
    CHECK(device.locationNumber());

    mtl::Buffer buffer = device.newBuffer(1024, mtl::ResourceOptions::StorageModePrivate);
    CHECK(device.currentAllocatedSize() > 0);
}

TEST_CASE("Blit command encoder")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();

    mtl::TextureDescriptor textureDescriptor;
    textureDescriptor.setTextureType(mtl::TextureType::Type2D);
    textureDescriptor.setWidth(1024);
    textureDescriptor.setHeight(1024);
    textureDescriptor.setUsage(mtl::TextureUsage::ShaderRead);
    textureDescriptor.setPixelFormat(mtl::PixelFormat::BGRA8Unorm);
    textureDescriptor.setStorageMode(mtl::StorageMode::Private);
    textureDescriptor.setMipmapLevelCount(10);

    mtl::Texture texture = device.newTexture(textureDescriptor);
    mtl::Texture destinationTexture = device.newTexture(textureDescriptor);
    mtl::Buffer buffer = device.newBuffer(2048, mtl::ResourceOptions::StorageModePrivate);
    mtl::Buffer destinationBuffer = device.newBuffer(2048, mtl::ResourceOptions::StorageModePrivate);

    mtl::BlitCommandEncoder blitCommandEncoder = commandBuffer.blitCommandEncoder();
    REQUIRE(blitCommandEncoder);
    CHECK(blitCommandEncoder.retainCount() == 2);
    blitCommandEncoder.setLabel("test");
    CHECK(blitCommandEncoder.label().isEqualToString("test"));

    blitCommandEncoder.generateMipmapsForTexture(texture);
    blitCommandEncoder.fillBuffer(buffer, ns::Range{0, 2048}, 10);

    blitCommandEncoder.copyFromTexture(texture, 0, 0, mtl::Origin{0, 0}, mtl::Size{1024, 1024, 1},
                                       destinationTexture, 0, 0, mtl::Origin{0, 0});

    blitCommandEncoder.copyFromBuffer(buffer, 0, 32 * 4, 2048, mtl::Size{32, 16, 1},
                                      destinationTexture, 0, 0, mtl::Origin{0, 0});

    blitCommandEncoder.copyFromTexture(texture, 0, 0, mtl::Origin{0, 0}, mtl::Size{32, 16, 1},
                                       destinationBuffer, 0, 32 * 4, 2048);

    blitCommandEncoder.copyFromBuffer(buffer, 0, destinationBuffer, 0, 2048);

    blitCommandEncoder.insertDebugSignpost("testSnippet");
    blitCommandEncoder.pushDebugGroup("testGroup");
    blitCommandEncoder.popDebugGroup();

    blitCommandEncoder.endEncoding();

    commandBuffer.commit();
    commandBuffer.waitUntilCompleted();
}

TEST_CASE("Buffer")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    mtl::Buffer buffer = device.newBuffer(1024, mtl::ResourceOptions::CPUCacheModeDefaultCache);
    REQUIRE(buffer);
    CHECK(buffer.retainCount() == 1);
    CHECK(buffer.length() == 1024);

    const char data[] = {'a', 'b', 'c', 'd'};
    mtl::Buffer bufferWithBytes = device.newBuffer(data, sizeof(data), mtl::ResourceOptions::StorageModeShared);
    REQUIRE(bufferWithBytes);
    CHECK(bufferWithBytes.retainCount() == 1);

    CHECK(bufferWithBytes.length() == sizeof(data));
    CHECK(buffer.gpuAddress());

    mtl::Buffer bufferManaged = device.newBuffer(1024, mtl::ResourceOptions::StorageModeManaged);
    bufferManaged.didModifyRange(ns::Range{0, 1024});

    buffer = nullptr;
}

TEST_CASE("Command buffer")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();
    REQUIRE(commandBuffer);
    CHECK(commandBuffer.retainCount() == 2); // one retain is autoreleased
    CHECK(commandBuffer.device() == device);

    char labelStr[] = "Command buffer";
    ns::String label{labelStr};
    CHECK(label.retainCount() == 1);
    commandBuffer.setLabel(label);
    CHECK(label.retainCount() > 0);
    CHECK(commandBuffer.label().isEqualToString(labelStr));

    commandBuffer.commit();
    commandBuffer.waitUntilCompleted();
}

TEST_CASE("Command queue")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    REQUIRE(commandQueue);
    CHECK(commandQueue.retainCount() == 1);
    CHECK(commandQueue.device() == device);

    CHECK(commandQueue.label().retainCount() == 0);
    char labelStr[] = "Command queue";
    ns::String label{labelStr};
    CHECK(label.retainCount() == 1);
    commandQueue.setLabel(label);
    CHECK(label.retainCount() > 0);

    CHECK(commandQueue.label().isEqualToString(labelStr));
    CHECK(commandQueue.label().retainCount() > 0);

    mtl::CommandQueue commandQueueWithMax = device.newCommandQueue(10);
    REQUIRE(commandQueueWithMax);
    CHECK(commandQueueWithMax.retainCount() == 1);

    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();
    REQUIRE(commandBuffer);
    CHECK(commandBuffer.retainCount() == 2); // one retain is autoreleased

    commandBuffer.commit();
    commandBuffer.waitUntilCompleted();
}

TEST_CASE("Compile options")
{
    ns::AutoreleasePool pool;

    mtl::CompileOptions options;
    REQUIRE(options);
    CHECK(options.retainCount() == 1);

    options.setFastMathEnabled(true);
    CHECK(options.fastMathEnabled());

    options.setLanguageVersion(mtl::LanguageVersion::Version1_1);
    CHECK(options.languageVersion() == mtl::LanguageVersion::Version1_1);

    options.setLibraryType(mtl::LibraryType::Dynamic);
    CHECK(options.libraryType() == mtl::LibraryType::Dynamic);
    options.setLibraryType(mtl::LibraryType::Executable);
    CHECK(options.libraryType() == mtl::LibraryType::Executable);

    options.setInstallName("Shader");
    CHECK(options.installName().isEqualToString("Shader"));

    options.setPreserveInstance(true);
    CHECK(options.preserveInvariance());

    options.setOptimizationLevel(mtl::LibraryOptimizationLevel::Size);
    CHECK(options.optimizationLevel() == mtl::LibraryOptimizationLevel::Size);

    {
        const ns::Dictionary<ns::String, ns::Object> preprocessorMacros{ns::String{"1.0"}, ns::String{"ONE"}};
        options.setPreprocessorMacros(preprocessorMacros);
        CHECK(options.preprocessorMacros());
        CHECK(options.preprocessorMacros().retainCount() == 3);
    }

    CHECK(options.preprocessorMacros());
    CHECK(options.preprocessorMacros().retainCount() == 2);
    CHECK(options.preprocessorMacros().retainCount() == 2);
}

TEST_CASE("Depth stencil state")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::DepthStencilDescriptor descriptor;
    REQUIRE(descriptor);
    CHECK(descriptor.retainCount());
    char labelStr[] = "Depth stencil state";
    ns::String label{labelStr};
    CHECK(label.retainCount() == 1);
    descriptor.setLabel(label);
    CHECK(label.retainCount() == 2);
    CHECK(descriptor.label().isEqualToString(labelStr));
    CHECK(descriptor.label().retainCount() == 3);
    CHECK(descriptor.label().retainCount() == 3);
    CHECK(descriptor.label().retainCount() == 3);

    mtl::DepthStencilState depthStencilState = device.newDepthStencilState(descriptor);
    REQUIRE(depthStencilState);
    CHECK(depthStencilState.retainCount());
    CHECK(depthStencilState.device() == device);

    CHECK(depthStencilState.label().isEqualToString(labelStr));
    CHECK(depthStencilState.label().retainCount() > 0);

    const auto retainCount = device.retainCount();
    {
        ns::AutoreleasePool autoreleasePool;

        mtl::Device depthStencilStateDevice = depthStencilState.device();
        CHECK(depthStencilStateDevice == device);

        autoreleasePool.drain();
        CHECK(device.retainCount() == retainCount + 1);
    }
    CHECK(device.retainCount() == retainCount);
}

TEST_CASE("Function")
{
    ns::AutoreleasePool pool;
    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    const char* vertexShader =
    "vertex float4 vsh(const device packed_float3 *vertexArray [[buffer(0)]], unsigned int vid [[vertex_id]]) {" \
    "    return float4(vertexArray[vid], 1.0);" \
    "}";

    mtl::Library vertexLibrary = device.newLibrary(vertexShader);
    mtl::Function vertexFunction = vertexLibrary.newFunction("vsh");
    REQUIRE(vertexFunction);
    CHECK(vertexFunction.device() == device);
    CHECK(vertexFunction.functionType() == mtl::FunctionType::Vertex);
    CHECK(vertexFunction.patchType() == mtl::PatchType::None);
    CHECK(vertexFunction.patchControlPointCount() == -1);
    //CHECK(vertexFunction.vertexAttributes());
    CHECK(vertexFunction.name().isEqualToString("vsh"));

    vertexFunction.setLabel("Vertex function");
    CHECK(vertexFunction.label().isEqualToString("Vertex function"));

    const char* fragmentShader =
    "constant float constant0 [[function_constant(0)]];\n" \
    "constant float constant1 [[function_constant(1)]];\n" \
    "constant float constant2 [[function_constant(2)]];\n" \
    "fragment half4 fsh() {" \
    "    return half4(1.0);" \
    "}";

    mtl::FunctionConstantValues constantValues;
    REQUIRE(constantValues);
    float value = 10.0F;
    constantValues.setConstantValue(&value, mtl::DataType::Float, 0);
    constantValues.setConstantValues(&value, mtl::DataType::Float, ns::Range{1, 1});
    constantValues.setConstantValue(&value, mtl::DataType::Float, "constant2");

    mtl::Library fragmentLibrary = device.newLibrary(fragmentShader);
    mtl::Function fragmentFunction = fragmentLibrary.newFunction("fsh", constantValues);
    REQUIRE(fragmentFunction);
    CHECK(fragmentFunction.functionType() == mtl::FunctionType::Fragment);
    CHECK(fragmentFunction.patchType() == mtl::PatchType::None);
    CHECK(fragmentFunction.patchControlPointCount() == -1);
    CHECK(fragmentFunction.name().isEqualToString("fsh"));

    const char* postTesselationShader =
    "[[patch(quad, 16)]]"
    "vertex float4 ptsh() { return float4{0.0, 0.0, 0.0, 0.0}; }";

    mtl::Library postTesselationLibrary = device.newLibrary(postTesselationShader);
    mtl::Function postTesselationFunction = postTesselationLibrary.newFunction("ptsh");
    REQUIRE(postTesselationFunction);
    CHECK(postTesselationFunction.functionType() == mtl::FunctionType::Vertex);
    CHECK(postTesselationFunction.patchType() == mtl::PatchType::Quad);
    CHECK(postTesselationFunction.patchControlPointCount() == 16);
    CHECK(postTesselationFunction.name().isEqualToString("ptsh"));

    const char* computeKernel =
    "kernel void ck() {}";

    mtl::Library computeLibrary = device.newLibrary(computeKernel);
    mtl::Function computeFunction = computeLibrary.newFunction("ck");
    REQUIRE(computeFunction);
    CHECK(computeFunction.functionType() == mtl::FunctionType::Kernel);
    CHECK(computeFunction.patchType() == mtl::PatchType::None);
    CHECK(computeFunction.patchControlPointCount() == -1);
    CHECK(computeFunction.name().isEqualToString("ck"));
}

TEST_CASE("Library")
{
    ns::AutoreleasePool pool;
    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    mtl::CompileOptions options;
    options.setLanguageVersion(mtl::LanguageVersion::Version1_1);
    const ns::Dictionary<ns::String, ns::Object> preprocessorMacros{ns::String{"1.0"}, ns::String{"ONE"}};
    options.setPreprocessorMacros(preprocessorMacros);

    const char* vertexShader =
    "vertex float4 vsh(const device packed_float3 *vertexArray [[buffer(0)]], unsigned int vid [[vertex_id]]) {" \
    "    return float4(vertexArray[vid], ONE);" \
    "}";

    mtl::Library library = device.newLibrary(vertexShader, options);
    REQUIRE(library);
    CHECK(library.retainCount() == 1);
    CHECK(library.device() == device);

    library.setLabel("Library");
    CHECK(library.label().isEqualToString("Library"));
}

TEST_CASE("Render command encoder")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();

    mtl::RenderPassDescriptor renderPassDescriptor;
    REQUIRE(renderPassDescriptor);
    CHECK(renderPassDescriptor.retainCount() == 1);

    mtl::TextureDescriptor textureDescriptor;
    textureDescriptor.setTextureType(mtl::TextureType::Type2D);
    textureDescriptor.setWidth(1024);
    textureDescriptor.setHeight(1024);
    textureDescriptor.setUsage(mtl::TextureUsage::ShaderRead);
    textureDescriptor.setPixelFormat(mtl::PixelFormat::BGRA8Unorm);
    textureDescriptor.setStorageMode(mtl::StorageMode::Private);
    textureDescriptor.setMipmapLevelCount(10);

    mtl::Texture texture = device.newTexture(textureDescriptor);

    mtl::SamplerDescriptor samplerDescriptor;
    mtl::SamplerState samplerState = device.newSamplerState(samplerDescriptor);

    mtl::TextureDescriptor renderTargetDescriptor;
    renderTargetDescriptor.setTextureType(mtl::TextureType::Type2D);
    renderTargetDescriptor.setWidth(1024);
    renderTargetDescriptor.setHeight(1024);
    renderTargetDescriptor.setUsage(mtl::TextureUsage::RenderTarget);
    renderTargetDescriptor.setPixelFormat(mtl::PixelFormat::BGRA8Unorm);
    renderTargetDescriptor.setStorageMode(mtl::StorageMode::Managed);

    mtl::Texture renderTarget = device.newTexture(renderTargetDescriptor);
    renderPassDescriptor.colorAttachments()[0].setTexture(renderTarget);
    renderPassDescriptor.colorAttachments()[0].setLoadAction(mtl::LoadAction::Clear);
    CHECK(renderPassDescriptor.colorAttachments()[0].loadAction() == mtl::LoadAction::Clear);
    renderPassDescriptor.colorAttachments()[0].setClearColor(mtl::ClearColor{1.0, 1.0, 0.0, 0.0});
    CHECK(renderPassDescriptor.colorAttachments()[0].clearColor() == mtl::ClearColor{1.0, 1.0, 0.0, 0.0});

    mtl::Buffer buffer = device.newBuffer(1024, mtl::ResourceOptions::StorageModePrivate);

    mtl::RenderCommandEncoder renderCommandEncoder = commandBuffer.renderCommandEncoder(renderPassDescriptor);
    REQUIRE(renderCommandEncoder);
    CHECK(renderCommandEncoder.retainCount() == 2);

    renderCommandEncoder.setVertexBuffer(buffer, 0, 0);
    renderCommandEncoder.setVertexTexture(texture, 0);
    renderCommandEncoder.setVertexTextures({texture, texture}, ns::Range{0, 2});
    renderCommandEncoder.setVertexSamplerState(samplerState, 0);
    renderCommandEncoder.setVertexSamplerStates({samplerState, samplerState}, ns::Range{0, 2});
    renderCommandEncoder.setViewport(mtl::Viewport{});
    renderCommandEncoder.setFrontFacingWinding(mtl::Winding::Clockwise);
    renderCommandEncoder.setCullMode(mtl::CullMode::Front);
    renderCommandEncoder.setDepthClipMode(mtl::DepthClipMode::Clip);
    renderCommandEncoder.setDepthBias(10.0F, 10.0F, 10.0F);
    renderCommandEncoder.setScissorRect(mtl::ScissorRect{0, 0, 100, 100});
    renderCommandEncoder.setTriangleFillMode(mtl::TriangleFillMode::Lines);
    renderCommandEncoder.setFragmentBuffer(buffer, 0, 0);
    renderCommandEncoder.setFragmentTexture(texture, 0);
    renderCommandEncoder.setFragmentTextures({texture, texture}, ns::Range{0, 2});
    renderCommandEncoder.setFragmentSamplerState(samplerState, 0);
    renderCommandEncoder.setFragmentSamplerStates({samplerState, samplerState}, ns::Range{0, 2});

    renderCommandEncoder.endEncoding();

    commandBuffer.commit();
    commandBuffer.waitUntilCompleted();
}

TEST_CASE("Render pipeline descriptor")
{
    ns::AutoreleasePool pool;
    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    const char* shader =
    "vertex float4 vsh(const device packed_float3 *vertexArray [[buffer(0)]], unsigned int vid [[vertex_id]]) {" \
    "    return float4(vertexArray[vid], 1.0);" \
    "}\n" \
    "fragment half4 fsh() {" \
    "    return half4(1.0);" \
    "}";

    mtl::Library library = device.newLibrary(shader);
    mtl::Function vertexFunction = library.newFunction("vsh");
    mtl::Function fragmentFunction = library.newFunction("fsh");

    mtl::RenderPipelineDescriptor renderPipelineDescriptor;
    REQUIRE(renderPipelineDescriptor);
    CHECK(renderPipelineDescriptor.retainCount() == 1);
    renderPipelineDescriptor.setLabel("Render pipeline");
    CHECK(renderPipelineDescriptor.label().isEqualToString("Render pipeline"));

    renderPipelineDescriptor.setVertexFunction(vertexFunction);
    CHECK(renderPipelineDescriptor.vertexFunction() == vertexFunction);
    renderPipelineDescriptor.setFragmentFunction(fragmentFunction);
    CHECK(renderPipelineDescriptor.fragmentFunction() == fragmentFunction);

    // depth and stencil attachments
    renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth32Float);
    CHECK(renderPipelineDescriptor.depthAttachmentPixelFormat() == mtl::PixelFormat::Depth32Float);
    renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
    CHECK(renderPipelineDescriptor.depthAttachmentPixelFormat() == mtl::PixelFormat::Depth24Unorm_Stencil8);
    // test stencil format setter with a different color format
    renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Stencil8);
    CHECK(renderPipelineDescriptor.stencilAttachmentPixelFormat() == mtl::PixelFormat::Stencil8);
    renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
    CHECK(renderPipelineDescriptor.stencilAttachmentPixelFormat() == mtl::PixelFormat::Depth24Unorm_Stencil8);
}

TEST_CASE("Render pipeline state")
{
    ns::AutoreleasePool pool;
    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    const char* shader =
    "vertex float4 vsh(const device packed_float3 *vertexArray [[buffer(0)]], unsigned int vid [[vertex_id]]) {" \
    "    return float4(vertexArray[vid], 1.0);" \
    "}\n" \
    "fragment half4 fsh() {" \
    "    return half4(1.0);" \
    "}";

    mtl::Library library = device.newLibrary(shader);
    mtl::Function vertexFunction = library.newFunction("vsh");
    mtl::Function fragmentFunction = library.newFunction("fsh");

    // vertex descriptor
    mtl::VertexDescriptor vertexDescriptor;

    mtl::VertexBufferLayoutDescriptorArray vertexLayouts = vertexDescriptor.layouts();

    mtl::VertexBufferLayoutDescriptor vertexLayout0 = vertexLayouts[0];
    vertexLayout0.setStride(16);
    vertexLayout0.setStepRate(1);
    vertexLayout0.setStepFunction(mtl::VertexStepFunction::PerVertex);

    mtl::VertexAttributeDescriptorArray vertexAttributes = vertexDescriptor.attributes();

    // position
    mtl::VertexAttributeDescriptor vertexAttribute0 = vertexAttributes[0];
    vertexAttribute0.setFormat(mtl::VertexFormat::Float3);
    vertexAttribute0.setOffset(0);
    vertexAttribute0.setBufferIndex(0);

    // color
    mtl::VertexAttributeDescriptor vertexAttribute1 = vertexAttributes[1];
    vertexAttribute1.setFormat(mtl::VertexFormat::UChar4Normalized);
    vertexAttribute1.setOffset(12);
    vertexAttribute1.setBufferIndex(0);

    // render pipeline descriptor
    mtl::RenderPipelineDescriptor renderPipelineDescriptor;
    renderPipelineDescriptor.setLabel("Render pipeline");
    renderPipelineDescriptor.setVertexFunction(vertexFunction);
    renderPipelineDescriptor.setFragmentFunction(fragmentFunction);
    renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
    renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);

    // color attachments
    mtl::RenderPipelineColorAttachmentDescriptorArray colorAttachments = renderPipelineDescriptor.colorAttachments();
    REQUIRE(colorAttachments);
    CHECK(colorAttachments.retainCount() == 2);
    
    colorAttachments[0].setBlendingEnabled(false);
    CHECK(colorAttachments[0].isBlendingEnabled() == false);
    colorAttachments[0].setBlendingEnabled(true);
    CHECK(colorAttachments[0].isBlendingEnabled() == true);

    colorAttachments[0].setSourceRGBBlendFactor(mtl::BlendFactor::SourceColor);
    CHECK(colorAttachments[0].sourceRGBBlendFactor() == mtl::BlendFactor::SourceColor);

    colorAttachments[0].setDestinationRGBBlendFactor(mtl::BlendFactor::BlendAlpha);
    CHECK(colorAttachments[0].destinationRGBBlendFactor() == mtl::BlendFactor::BlendAlpha);

    colorAttachments[0].setRgbBlendOperation(mtl::BlendOperation::Max);
    CHECK(colorAttachments[0].rgbBlendOperation() == mtl::BlendOperation::Max);

    colorAttachments[0].setSourceAlphaBlendFactor(mtl::BlendFactor::BlendColor);
    CHECK(colorAttachments[0].sourceAlphaBlendFactor() == mtl::BlendFactor::BlendColor);

    colorAttachments[0].setDestinationAlphaBlendFactor(mtl::BlendFactor::SourceAlphaSaturated);
    CHECK(colorAttachments[0].destinationAlphaBlendFactor() == mtl::BlendFactor::SourceAlphaSaturated);

    colorAttachments[0].setAlphaBlendOperation(mtl::BlendOperation::Min);
    CHECK(colorAttachments[0].alphaBlendOperation() == mtl::BlendOperation::Min);

    colorAttachments[0].setWriteMask(mtl::ColorWriteMask::Blue | mtl::ColorWriteMask::Green);
    CHECK(colorAttachments[0].writeMask() == (mtl::ColorWriteMask::Blue | mtl::ColorWriteMask::Green));

    renderPipelineDescriptor.setVertexDescriptor(vertexDescriptor);

    // render pipeline state
    mtl::RenderPipelineState renderPipelineState = device.newRenderPipelineState(renderPipelineDescriptor);
    REQUIRE(renderPipelineState);
    CHECK(renderPipelineState.retainCount() == 1);
    CHECK(renderPipelineState.device() == device);
    CHECK(renderPipelineState.label().isEqualToString("Render pipeline"));
}

TEST_CASE("Sampler descriptor")
{
    ns::AutoreleasePool pool;
    mtl::SamplerDescriptor samplerDescriptor;
    REQUIRE(samplerDescriptor);
    CHECK(samplerDescriptor.retainCount() == 1);

    CHECK(samplerDescriptor.minFilter() != mtl::SamplerMinMagFilter::Linear);
    samplerDescriptor.setMinFilter(mtl::SamplerMinMagFilter::Linear);
    CHECK(samplerDescriptor.minFilter() == mtl::SamplerMinMagFilter::Linear);

    CHECK(samplerDescriptor.magFilter() != mtl::SamplerMinMagFilter::Linear);
    samplerDescriptor.setMagFilter(mtl::SamplerMinMagFilter::Linear);
    CHECK(samplerDescriptor.magFilter() == mtl::SamplerMinMagFilter::Linear);

    CHECK(samplerDescriptor.mipFilter() != mtl::SamplerMipFilter::Linear);
    samplerDescriptor.setMipFilter(mtl::SamplerMipFilter::Linear);
    CHECK(samplerDescriptor.mipFilter() == mtl::SamplerMipFilter::Linear);

    CHECK(samplerDescriptor.maxAnisotropy() != 11);
    samplerDescriptor.setMaxAnisotropy(11);
    CHECK(samplerDescriptor.maxAnisotropy() == 11);

    CHECK(samplerDescriptor.sAddressMode() != mtl::SamplerAddressMode::MirrorRepeat);
    samplerDescriptor.setSAddressMode(mtl::SamplerAddressMode::MirrorRepeat);
    CHECK(samplerDescriptor.sAddressMode() == mtl::SamplerAddressMode::MirrorRepeat);

    CHECK(samplerDescriptor.tAddressMode() != mtl::SamplerAddressMode::ClampToZero);
    samplerDescriptor.setTAddressMode(mtl::SamplerAddressMode::ClampToZero);
    CHECK(samplerDescriptor.tAddressMode() == mtl::SamplerAddressMode::ClampToZero);

    CHECK(samplerDescriptor.rAddressMode() != mtl::SamplerAddressMode::ClampToBorderColor);
    samplerDescriptor.setRAddressMode(mtl::SamplerAddressMode::ClampToBorderColor);
    CHECK(samplerDescriptor.rAddressMode() == mtl::SamplerAddressMode::ClampToBorderColor);

    CHECK(samplerDescriptor.borderColor() != mtl::SamplerBorderColor::OpaqueWhite);
    samplerDescriptor.setBorderColor(mtl::SamplerBorderColor::OpaqueWhite);
    CHECK(samplerDescriptor.borderColor() == mtl::SamplerBorderColor::OpaqueWhite);

    CHECK(samplerDescriptor.normalizedCoordinates() != false);
    samplerDescriptor.setNormalizedCoordinates(false);
    CHECK(samplerDescriptor.normalizedCoordinates() == false);

    CHECK(samplerDescriptor.lodMinClamp() != 2.0F);
    samplerDescriptor.setLodMinClamp(2.0F);
    CHECK(samplerDescriptor.lodMinClamp() == 2.0F);

    CHECK(samplerDescriptor.lodMaxClamp() != 2.0F);
    samplerDescriptor.setLodMaxClamp(2.0F);
    CHECK(samplerDescriptor.lodMaxClamp() == 2.0F);

    CHECK(samplerDescriptor.lodAverage() != true);
    samplerDescriptor.setLodAverage(true);
    CHECK(samplerDescriptor.lodAverage() == true);

    CHECK(samplerDescriptor.compareFunction() != mtl::CompareFunction::GreaterEqual);
    samplerDescriptor.setCompareFunction(mtl::CompareFunction::GreaterEqual);
    CHECK(samplerDescriptor.compareFunction() == mtl::CompareFunction::GreaterEqual);

    CHECK(samplerDescriptor.supportArgumentBuffers() != true);
    samplerDescriptor.setSupportArgumentBuffers(true);
    CHECK(samplerDescriptor.supportArgumentBuffers() == true);

    samplerDescriptor.setLabel("Sampler");
    CHECK(samplerDescriptor.label().isEqualToString("Sampler"));
}

TEST_CASE("Sampler state")
{
    ns::AutoreleasePool pool;
    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::SamplerDescriptor samplerDescriptor;
    samplerDescriptor.setLabel("Sampler");

    mtl::SamplerState samplerState = device.newSamplerState(samplerDescriptor);
    REQUIRE(samplerState);
    CHECK(samplerState.retainCount());

    CHECK(samplerState.device() == device);
    CHECK(samplerState.label().isEqualToString("Sampler"));
}

TEST_CASE("Texture")
{
    ns::AutoreleasePool pool;
    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    mtl::TextureDescriptor textureDescriptor;
    REQUIRE(textureDescriptor);
    CHECK(textureDescriptor.retainCount() == 1);
    textureDescriptor.setTextureType(mtl::TextureType::Type2D);
    CHECK(textureDescriptor.textureType() == mtl::TextureType::Type2D);
    textureDescriptor.setPixelFormat(mtl::PixelFormat::BGRA8Unorm);
    CHECK(textureDescriptor.pixelFormat() == mtl::PixelFormat::BGRA8Unorm);

    textureDescriptor.setWidth(1024);
    CHECK(textureDescriptor.width() == 1024);
    textureDescriptor.setHeight(768);
    CHECK(textureDescriptor.height() == 768);

    textureDescriptor.setDepth(10);
    CHECK(textureDescriptor.depth() == 10);
    textureDescriptor.setDepth(1);
    CHECK(textureDescriptor.depth() == 1);

    textureDescriptor.setMipmapLevelCount(20);
    CHECK(textureDescriptor.mipmapLevelCount() == 20);
    textureDescriptor.setMipmapLevelCount(2);
    CHECK(textureDescriptor.mipmapLevelCount() == 2);

    textureDescriptor.setSampleCount(4);
    CHECK(textureDescriptor.sampleCount() == 4);
    textureDescriptor.setSampleCount(1);
    CHECK(textureDescriptor.sampleCount() == 1);

    textureDescriptor.setArrayLength(8);
    CHECK(textureDescriptor.arrayLength() == 8);
    textureDescriptor.setArrayLength(1);
    CHECK(textureDescriptor.arrayLength() == 1);

    textureDescriptor.setCpuCacheMode(mtl::CPUCacheMode::WriteCombined);
    CHECK(textureDescriptor.cpuCacheMode() == mtl::CPUCacheMode::WriteCombined);

    textureDescriptor.setStorageMode(mtl::StorageMode::Managed);
    CHECK(textureDescriptor.storageMode() == mtl::StorageMode::Managed);

    textureDescriptor.setHazardTrackingMode(mtl::HazardTrackingMode::Tracked);
    CHECK(textureDescriptor.hazardTrackingMode() == mtl::HazardTrackingMode::Tracked);

    textureDescriptor.setUsage(mtl::TextureUsage::RenderTarget);
    CHECK(textureDescriptor.usage() == mtl::TextureUsage::RenderTarget);

    textureDescriptor.setCompressionType(mtl::TextureCompressionType::Lossy);
    CHECK(textureDescriptor.compressionType() == mtl::TextureCompressionType::Lossy);
    textureDescriptor.setCompressionType(mtl::TextureCompressionType::Lossless);
    CHECK(textureDescriptor.compressionType() == mtl::TextureCompressionType::Lossless);

    mtl::Texture texture = device.newTexture(textureDescriptor);
    REQUIRE(texture);
    CHECK(texture.retainCount() == 1);

    CHECK(texture.textureType() == mtl::TextureType::Type2D);
    CHECK(texture.pixelFormat() == mtl::PixelFormat::BGRA8Unorm);
    CHECK(texture.width() == 1024);
    CHECK(texture.height() == 768);
    CHECK(texture.depth() == 1);
    CHECK(texture.mipmapLevelCount() == 2);
    CHECK(texture.sampleCount() == 1);
    CHECK(texture.arrayLength() == 1);
    CHECK(texture.usage() == mtl::TextureUsage::RenderTarget);
    CHECK(texture.compressionType() == mtl::TextureCompressionType::Lossless);

    std::uint8_t level0[] = {
        0xFFU, 0xFFU, 0xFFU, 0xFFU, 0x00U, 0x00U, 0x00U, 0xFFU,
        0x00U, 0x00U, 0x00U, 0xFFU, 0xFFU, 0xFFU, 0xFFU, 0xFFU
    };
    std::uint8_t level1[] = {
        0xFFU, 0xFFU, 0xFFU, 0xFFU
    };
    texture.replaceRegion(mtl::Region{0, 0, 0, 2, 2, 1}, 0, level0, 8);
    texture.replaceRegion(mtl::Region{0, 0, 0, 1, 1, 1}, 1, level1, 4);
}

TEST_CASE("Vertex descriptor")
{
    ns::AutoreleasePool pool;

    mtl::VertexDescriptor vertexDescriptor;
    REQUIRE(vertexDescriptor);
    CHECK(vertexDescriptor.retainCount() == 1);

    mtl::VertexBufferLayoutDescriptorArray vertexLayouts = vertexDescriptor.layouts();

    mtl::VertexBufferLayoutDescriptor vertexLayout0 = vertexLayouts[0];
    vertexLayout0.setStride(16);
    CHECK(vertexLayout0.stride() == 16);
    vertexLayout0.setStepRate(1);
    CHECK(vertexLayout0.stepRate() == 1);
    vertexLayout0.setStepFunction(mtl::VertexStepFunction::PerVertex);
    CHECK(vertexLayout0.stepFunction() == mtl::VertexStepFunction::PerVertex);

    mtl::VertexAttributeDescriptorArray vertexAttributes = vertexDescriptor.attributes();
    REQUIRE(vertexAttributes);
    CHECK(vertexAttributes.retainCount() == 2);

    mtl::VertexAttributeDescriptor vertexAttribute0 = vertexAttributes[0];
    REQUIRE(vertexAttribute0);
    CHECK(vertexAttribute0.retainCount() == 2);

    vertexAttribute0.setFormat(mtl::VertexFormat::Float3);
    CHECK(vertexAttribute0.format() == mtl::VertexFormat::Float3);
    vertexAttribute0.setOffset(0);
    CHECK(vertexAttribute0.offset() == 0);
    vertexAttribute0.setBufferIndex(0);
    CHECK(vertexAttribute0.bufferIndex() == 0);
}
