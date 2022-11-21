#include "doctest.h"
#include "quartzcore/Layer.hpp"
#include "quartzcore/MetalLayer.hpp"

TEST_CASE("Layer")
{
    ca::Layer layer;
    REQUIRE(layer);
    REQUIRE(layer.retainCount() == 1);
    REQUIRE(layer.getClass() == objc_getClass("CALayer"));
}

TEST_CASE("MetalLayer")
{
    ca::MetalLayer metalLayer;
    REQUIRE(metalLayer);
    REQUIRE(metalLayer.retainCount());
    REQUIRE(metalLayer.getClass() == objc_getClass("CAMetalLayer"));
}
