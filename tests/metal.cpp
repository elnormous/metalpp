#define DOCTEST_CONFIG_USE_STD_HEADERS
#include "doctest.h"
#include "metal/Metal.hpp"

TEST_CASE("Device")
{
    mtl::Device device;
    REQUIRE(device);
}
