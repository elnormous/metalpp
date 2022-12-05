#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "quartzcore/Layer.hpp"
#include "quartzcore/MetalLayer.hpp"

TEST_CASE("Layer")
{
    ns::AutoreleasePool pool;

    ca::Layer layer;
    REQUIRE(layer);
    CHECK(layer.retainCount() == 1);
    CHECK(layer.getClass() == objc_getClass("CALayer"));
    layer.setFrame(cg::Rect{0, 0, 100, 100});
    CHECK(layer.frame() == cg::Rect{0, 0, 100, 100});
    layer.setMinificationFilter(ca::FilterLinear);
    CHECK(layer.minificationFilter().isEqualToString(ca::FilterLinear));
    layer.setMinificationFilter(ca::FilterNearest);
    CHECK(layer.minificationFilter().isEqualToString(ca::FilterNearest));

    layer.setMagnificationFilter(ca::FilterLinear);
    CHECK(layer.magnificationFilter().isEqualToString(ca::FilterLinear));
    layer.setMagnificationFilter(ca::FilterNearest);
    CHECK(layer.magnificationFilter().isEqualToString(ca::FilterNearest));
}

TEST_CASE("MetalLayer")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    ca::MetalLayer metalLayer;
    REQUIRE(metalLayer);
    CHECK(metalLayer.retainCount());
    CHECK(metalLayer.getClass() == objc_getClass("CAMetalLayer"));

    metalLayer.setDevice(device);
    CHECK(metalLayer.device() == device);
}

TEST_CASE("MetalDrawable")
{
    ns::AutoreleasePool pool;

    mtl::Device device = mtl::Device::createSystemDefaultDevice();

    ca::MetalLayer metalLayer;
    metalLayer.setDevice(device);

//    ca::MetalDrawable metalDrawable = metalLayer.nextDrawable();
//    REQUIRE(metalDrawable);
//    CHECK(metalDrawable.retainCount());
};
