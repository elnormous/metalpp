#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "metal/Metal.hpp"

TEST_CASE("Device")
{
    mtl::Device device;
    REQUIRE(device);
}

TEST_CASE("Device name")
{
    mtl::Device device;
    const ns::String name = device.name();
    REQUIRE(name);
    REQUIRE(name.retainCount());
    CHECK(name.length());
}

TEST_CASE("Command queue")
{
    mtl::Device device;
    mtl::CommandQueue commandQueue = device.newCommandQueue();
    REQUIRE(commandQueue);
    REQUIRE(commandQueue.retainCount() == 1);

    CHECK(commandQueue.label().retainCount() == 0);
    char labelStr[] = "Command queue";
    ns::String label{labelStr};
    CHECK(label.retainCount() == 1);
    commandQueue.setLabel(label);
    CHECK(label.retainCount() > 0);

    CHECK(commandQueue.label().isEqualToString(labelStr));
    CHECK(commandQueue.label().retainCount() > 0);

    mtl::CommandQueue commandQueueWithMax = device.newCommandQueueWithMaxCommandBufferCount(10);
    REQUIRE(commandQueueWithMax);
    REQUIRE(commandQueueWithMax.retainCount() == 1);

    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();
    REQUIRE(commandBuffer);
    REQUIRE(commandBuffer.retainCount() == 2); // one retain is autoreleased
}

TEST_CASE("Depth stencil state")
{
    mtl::Device device;
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

    mtl::DepthStencilState depthStencilState = device.newDepthStencilStateWithDescriptor(descriptor);
    REQUIRE(depthStencilState);
    REQUIRE(depthStencilState.retainCount());
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

TEST_CASE("Render pipeline state")
{
    const char* vertexShader =
    "vertex float4 vsh_flat(const device packed_float3 *vertexArray [[ buffer(0) ]], unsigned int vid [[ vertex_id ]]) {" \
    "    return float4(vertexArray[vid], ONE);" \
    "}";

    const char* fragmentShader =
    "fragment half4 fsh_flat() {" \
    "    return half4(1.0);" \
    "}";

    mtl::Device device;

    // compile options
    mtl::CompileOptions options;
    REQUIRE(options);
    REQUIRE(options.retainCount() == 1);
    options.setLanguageVersion(mtl::LanguageVersion::Version1_1);
    CHECK(options.languageVersion() == mtl::LanguageVersion::Version1_1);
    options.setFastMathEnabled(true);
    CHECK(options.fastMathEnabled());

    {
        const ns::Dictionary<ns::String, ns::Object> preprocessorMacros{ns::String{"1.0"}, ns::String{"ONE"}};
        options.setPreprocessorMacros(preprocessorMacros);
        CHECK(options.preprocessorMacros().retainCount() == 3);
    }

    CHECK(options.preprocessorMacros());
    CHECK(options.preprocessorMacros().retainCount() == 2);
    CHECK(options.preprocessorMacros().retainCount() == 2);

    // vertex shader
    mtl::Library vertexLibrary = device.newLibraryWithSource(ns::String{vertexShader}, options);
    REQUIRE(vertexLibrary);
    REQUIRE(vertexLibrary.retainCount() == 1);
    vertexLibrary.setLabel("Vertex library");
    CHECK(vertexLibrary.label().isEqualToString("Vertex library"));

    mtl::Function vertexFunction = vertexLibrary.newFunctionWithName(ns::String{"vsh_flat"});

    // fragment shader
    mtl::Library fragmentLibrary = device.newLibraryWithSource(ns::String{fragmentShader});
    REQUIRE(fragmentLibrary);
    REQUIRE(fragmentLibrary.retainCount() == 1);
    fragmentLibrary.setLabel("Fragment library");
    CHECK(fragmentLibrary.label().isEqualToString("Fragment library"));

    mtl::Function fragmentFunction = fragmentLibrary.newFunctionWithName(ns::String{"fsh_flat"});

    // vertex descriptor
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

    // position
    mtl::VertexAttributeDescriptor vertexAttribute0 = vertexAttributes[0];
    REQUIRE(vertexAttribute0);
    REQUIRE(vertexAttribute0.retainCount() == 2);

    vertexAttribute0.setFormat(mtl::VertexFormat::Float3);
    CHECK(vertexAttribute0.format() == mtl::VertexFormat::Float3);
    vertexAttribute0.setOffset(0);
    CHECK(vertexAttribute0.offset() == 0);
    vertexAttribute0.setBufferIndex(0);
    CHECK(vertexAttribute0.bufferIndex() == 0);

    // color
    mtl::VertexAttributeDescriptor vertexAttribute1 = vertexAttributes[1];
    REQUIRE(vertexAttribute1);
    REQUIRE(vertexAttribute1.retainCount() == 2);

    vertexAttribute1.setFormat(mtl::VertexFormat::UChar4Normalized);
    CHECK(vertexAttribute1.format() == mtl::VertexFormat::UChar4Normalized);
    vertexAttribute1.setOffset(12);
    CHECK(vertexAttribute1.offset() == 12);
    vertexAttribute1.setBufferIndex(0);

    // render pipeline descriptor
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
    renderPipelineDescriptor.setDepthAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
    CHECK(renderPipelineDescriptor.depthAttachmentPixelFormat() == mtl::PixelFormat::Depth24Unorm_Stencil8);
    // test stencil format setter with a different color format
    renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Stencil8);
    CHECK(renderPipelineDescriptor.stencilAttachmentPixelFormat() == mtl::PixelFormat::Stencil8);
    renderPipelineDescriptor.setStencilAttachmentPixelFormat(mtl::PixelFormat::Depth24Unorm_Stencil8);
    CHECK(renderPipelineDescriptor.stencilAttachmentPixelFormat() == mtl::PixelFormat::Depth24Unorm_Stencil8);

    // color attachments
    mtl::RenderPipelineColorAttachmentDescriptorArray colorAttachments = renderPipelineDescriptor.colorAttachments();
    REQUIRE(colorAttachments);
    REQUIRE(colorAttachments.retainCount() == 2);

    renderPipelineDescriptor.setVertexDescriptor(vertexDescriptor);

    // render pipeline state
    mtl::RenderPipelineState renderPipelineState = device.newRenderPipelineStateWithDescriptor(renderPipelineDescriptor);
    REQUIRE(renderPipelineState);
    REQUIRE(renderPipelineState.retainCount() == 1);
}
