#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "quartzcore/Layer.hpp"
#include "quartzcore/MetalLayer.hpp"

TEST_CASE("Layer")
{
    ns::AutoreleasePool pool;

    ca::Layer layer;
    REQUIRE(layer);
    REQUIRE(layer.retainCount() == 1);
    REQUIRE(layer.getClass() == objc_getClass("CALayer"));
    layer.setFrame(cg::Rect{0, 0, 100, 100});
    CHECK(layer.frame() == cg::Rect{0, 0, 100, 100});
    layer.setMinificationFilter(ca::filterLinear);
    CHECK(layer.minificationFilter().isEqualToString(ca::filterLinear));
    layer.setMinificationFilter(ca::filterNearest);
    CHECK(layer.minificationFilter().isEqualToString(ca::filterNearest));

    layer.setMagnificationFilter(ca::filterLinear);
    CHECK(layer.magnificationFilter().isEqualToString(ca::filterLinear));
    layer.setMagnificationFilter(ca::filterNearest);
    CHECK(layer.magnificationFilter().isEqualToString(ca::filterNearest));
}

TEST_CASE("MetalLayer")
{
    ns::AutoreleasePool pool;

    mtl::Device device;

    ca::MetalLayer metalLayer;
    REQUIRE(metalLayer);
    REQUIRE(metalLayer.retainCount());
    REQUIRE(metalLayer.getClass() == objc_getClass("CAMetalLayer"));

    metalLayer.setDevice(device);
    CHECK(metalLayer.device() == device);
}

TEST_CASE("MetalDrawable")
{
    ns::AutoreleasePool pool;

    mtl::Device device;

    ca::MetalLayer metalLayer;
    metalLayer.setDevice(device);

//    ca::MetalDrawable metalDrawable = metalLayer.nextDrawable();
//    REQUIRE(metalDrawable);
//    REQUIRE(metalDrawable.retainCount());
};
