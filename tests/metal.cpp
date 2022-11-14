#include "doctest.h"
#include "metal/Metal.hpp"

TEST_CASE("Device")
{
    mtl::Device device;
    REQUIRE(device);
}
