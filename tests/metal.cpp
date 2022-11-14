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
