#include "doctest.h"
#include "coregraphics/ColorSpace.hpp"

TEST_CASE("ColorSpace")
{
    cg::ColorSpace colorSpace = cg::ColorSpace::deviceRGB();
    CHECK(colorSpace);
    CHECK(colorSpace.retainCount());
}
