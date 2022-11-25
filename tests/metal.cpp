#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "metal/Metal.hpp"

TEST_CASE("Device")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    REQUIRE(device);
}

TEST_CASE("Device name")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    const ns::String name = device.name();
    REQUIRE(name);
    REQUIRE(name.retainCount());
    CHECK(name.length());
}

TEST_CASE("Buffer")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    mtl::Buffer buffer = device.newBuffer(1024, mtl::ResourceOptions::CPUCacheModeDefaultCache);
    REQUIRE(buffer);
    REQUIRE(buffer.retainCount() == 1);
    CHECK(buffer.length() == 1024);

    const char data[] = {'a', 'b', 'c', 'd'};
    mtl::Buffer bufferWithBytes = device.newBuffer(data, sizeof(data), mtl::ResourceOptions::StorageModeShared);
    REQUIRE(bufferWithBytes);
    REQUIRE(bufferWithBytes.retainCount() == 1);

    CHECK(bufferWithBytes.length() == sizeof(data));
    CHECK(buffer.gpuAddress());

    mtl::Buffer bufferManaged = device.newBuffer(1024, mtl::ResourceOptions::StorageModeManaged);
    bufferManaged.didModifyRange(ns::Range{0, 1024});
}

TEST_CASE("Command queue")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    REQUIRE(commandQueue);
    REQUIRE(commandQueue.retainCount() == 1);
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
    REQUIRE(commandQueueWithMax.retainCount() == 1);

    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();
    REQUIRE(commandBuffer);
    REQUIRE(commandBuffer.retainCount() == 2); // one retain is autoreleased
}

TEST_CASE("Command buffer")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();
    REQUIRE(commandBuffer);
    REQUIRE(commandBuffer.retainCount() == 2); // one retain is autoreleased
    CHECK(commandBuffer.device() == device);

    char labelStr[] = "Command buffer";
    ns::String label{labelStr};
    CHECK(label.retainCount() == 1);
    commandBuffer.setLabel(label);
    CHECK(label.retainCount() > 0);
    CHECK(commandBuffer.label().isEqualToString(labelStr));

    mtl::RenderPassDescriptor renderPassDescriptor;
    REQUIRE(renderPassDescriptor);
    REQUIRE(renderPassDescriptor.retainCount() == 1);

    mtl::BlitCommandEncoder blitCommandEncoder = commandBuffer.blitCommandEncoder();
    REQUIRE(blitCommandEncoder);
    REQUIRE(blitCommandEncoder.retainCount() == 2);

    blitCommandEncoder.endEncoding();

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

    mtl::RenderCommandEncoder renderCommandEncoder = commandBuffer.renderCommandEncoder(renderPassDescriptor);
    REQUIRE(renderCommandEncoder);
    REQUIRE(renderCommandEncoder.retainCount() == 2);

    renderCommandEncoder.endEncoding();

    commandBuffer.commit();
    commandBuffer.waitUntilCompleted();
}

TEST_CASE("Depth stencil state")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();
    mtl::DepthStencilDescriptor descriptor;
    REQUIRE(descriptor);
    REQUIRE(descriptor.retainCount());
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
    REQUIRE(depthStencilState.retainCount());
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

TEST_CASE("Compile options")
{
    ns::AutoreleasePool pool;

    mtl::CompileOptions options;
    REQUIRE(options);
    REQUIRE(options.retainCount() == 1);

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
    REQUIRE(library.retainCount() == 1);
    CHECK(library.device() == device);

    library.setLabel("Library");
    CHECK(library.label().isEqualToString("Library"));
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
    CHECK(vertexFunction.device() == device);
    CHECK(vertexFunction.functionType() == mtl::FunctionType::Vertex);
    CHECK(vertexFunction.patchType() == mtl::PatchType::None);
    CHECK(vertexFunction.patchControlPointCount() == -1);
    //CHECK(vertexFunction.vertexAttributes());
    CHECK(vertexFunction.name().isEqualToString("vsh"));

    vertexFunction.setLabel("Vertex function");
    CHECK(vertexFunction.label().isEqualToString("Vertex function"));

    const char* fragmentShader =
    "fragment half4 fsh() {" \
    "    return half4(1.0);" \
    "}";

    mtl::Library fragmentLibrary = device.newLibrary(fragmentShader);
    mtl::Function fragmentFunction = fragmentLibrary.newFunction("fsh");
    CHECK(fragmentFunction.functionType() == mtl::FunctionType::Fragment);
    CHECK(fragmentFunction.patchType() == mtl::PatchType::None);
    CHECK(fragmentFunction.patchControlPointCount() == -1);
    CHECK(fragmentFunction.name().isEqualToString("fsh"));

    const char* postTesselationShader =
    "[[patch(quad, 16)]]"
    "vertex float4 ptsh() { return float4{0.0, 0.0, 0.0, 0.0}; }";

    mtl::Library postTesselationLibrary = device.newLibrary(postTesselationShader);
    mtl::Function postTesselationFunction = postTesselationLibrary.newFunction("ptsh");
    CHECK(postTesselationFunction.functionType() == mtl::FunctionType::Vertex);
    CHECK(postTesselationFunction.patchType() == mtl::PatchType::Quad);
    CHECK(postTesselationFunction.patchControlPointCount() == 16);
    CHECK(postTesselationFunction.name().isEqualToString("ptsh"));

    const char* computeKernel =
    "kernel void ck() {}";

    mtl::Library computeLibrary = device.newLibrary(computeKernel);
    mtl::Function computeFunction = computeLibrary.newFunction("ck");
    CHECK(computeFunction.functionType() == mtl::FunctionType::Kernel);
    CHECK(computeFunction.patchType() == mtl::PatchType::None);
    CHECK(computeFunction.patchControlPointCount() == -1);
    CHECK(computeFunction.name().isEqualToString("ck"));
}

TEST_CASE("Vertex descriptor")
{
    ns::AutoreleasePool pool;

    mtl::VertexDescriptor vertexDescriptor;
    REQUIRE(vertexDescriptor);
    REQUIRE(vertexDescriptor.retainCount() == 1);

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
    REQUIRE(vertexAttributes.retainCount() == 2);

    mtl::VertexAttributeDescriptor vertexAttribute0 = vertexAttributes[0];
    REQUIRE(vertexAttribute0);
    REQUIRE(vertexAttribute0.retainCount() == 2);

    vertexAttribute0.setFormat(mtl::VertexFormat::Float3);
    CHECK(vertexAttribute0.format() == mtl::VertexFormat::Float3);
    vertexAttribute0.setOffset(0);
    CHECK(vertexAttribute0.offset() == 0);
    vertexAttribute0.setBufferIndex(0);
    CHECK(vertexAttribute0.bufferIndex() == 0);
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
    REQUIRE(renderPipelineDescriptor.retainCount() == 1);
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
    REQUIRE(colorAttachments.retainCount() == 2);
    
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
    REQUIRE(renderPipelineState.retainCount() == 1);
    CHECK(renderPipelineState.device() == device);
    CHECK(renderPipelineState.label().isEqualToString("Render pipeline"));
}

TEST_CASE("Texture")
{
    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    mtl::TextureDescriptor textureDescriptor;
    REQUIRE(textureDescriptor);
    REQUIRE(textureDescriptor.retainCount() == 1);
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
    textureDescriptor.setMipmapLevelCount(1);
    CHECK(textureDescriptor.mipmapLevelCount() == 1);

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
    REQUIRE(texture.retainCount() == 1);

    CHECK(texture.textureType() == mtl::TextureType::Type2D);
    CHECK(texture.pixelFormat() == mtl::PixelFormat::BGRA8Unorm);
    CHECK(texture.width() == 1024);
    CHECK(texture.height() == 768);
    CHECK(texture.depth() == 1);
    CHECK(texture.mipmapLevelCount() == 1);
    CHECK(texture.sampleCount() == 1);
    CHECK(texture.arrayLength() == 1);
    CHECK(texture.usage() == mtl::TextureUsage::RenderTarget);
    CHECK(texture.compressionType() == mtl::TextureCompressionType::Lossless);
}

TEST_CASE("Samples")
{
}
