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
    REQUIRE(commandQueue.retainCount());

    mtl::CommandQueue commandQueueWithMax = device.newCommandQueueWithMaxCommandBufferCount(10);
    REQUIRE(commandQueueWithMax);
    REQUIRE(commandQueueWithMax.retainCount());

    mtl::CommandBuffer commandBuffer = commandQueue.commandBuffer();
    REQUIRE(commandBuffer);
    REQUIRE(commandBuffer.retainCount());
}

TEST_CASE("Depth stencil state")
{
    mtl::Device device;
    mtl::DepthStencilDescriptor descriptor;
    REQUIRE(descriptor);
    REQUIRE(descriptor.retainCount());

    mtl::DepthStencilState depthStencilState = device.newDepthStencilStateWithDescriptor(descriptor);
    REQUIRE(depthStencilState);
    REQUIRE(depthStencilState.retainCount());

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
    "    return float4(vertexArray[vid], 1.0);" \
    "}";

    const char* fragmentShader =
    "fragment half4 fsh_flat() {" \
    "    return half4(1.0);" \
    "}";

    mtl::Device device;

    mtl::RenderPipelineDescriptor renderPipelineDescriptor;
    REQUIRE(renderPipelineDescriptor);
    REQUIRE(renderPipelineDescriptor.retainCount() == 1);
    renderPipelineDescriptor.setLabel("Render pipeline");
    CHECK(renderPipelineDescriptor.label().string() == "Render pipeline");

    mtl::CompileOptions options;
    REQUIRE(options);
    REQUIRE(options.retainCount() == 1);
    options.setLanguageVersion(mtl::LanguageVersion::Version1_1);
    CHECK(options.languageVersion() == mtl::LanguageVersion::Version1_1);
    options.setFastMathEnabled(true);
    CHECK(options.fastMathEnabled());

    const ns::Dictionary<ns::String, ns::Object> preprocessorMacros{ns::String{"1.0"}, ns::String{"ONE"}};
    options.setPreprocessorMacros(preprocessorMacros);

    // vertex shader
    mtl::Library vertexLibrary = device.newLibraryWithSource(ns::String{vertexShader}, options);
    REQUIRE(vertexLibrary);
    REQUIRE(vertexLibrary.retainCount() == 1);
    vertexLibrary.setLabel("Vertex library");
    CHECK(vertexLibrary.label().string() == "Vertex library");

    mtl::Function vertexFunction = vertexLibrary.newFunctionWithName(ns::String{"mainVS"});
    renderPipelineDescriptor.setVertexFunction(vertexFunction);
    CHECK(renderPipelineDescriptor.vertexFunction() == vertexFunction);

    // fragment shader
    mtl::Library fragmentLibrary = device.newLibraryWithSource(ns::String{fragmentShader});
    REQUIRE(fragmentLibrary);
    REQUIRE(fragmentLibrary.retainCount() == 1);
    fragmentLibrary.setLabel("Fragment library");
    CHECK(fragmentLibrary.label().string() == "Fragment library");

    mtl::Function fragmentFunction = fragmentLibrary.newFunctionWithName(ns::String{"mainPS"});
    renderPipelineDescriptor.setFragmentFunction(fragmentFunction);
    CHECK(renderPipelineDescriptor.fragmentFunction() == fragmentFunction);
}
