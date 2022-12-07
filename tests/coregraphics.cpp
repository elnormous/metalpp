#include "doctest.h"
#include "coregraphics/Color.hpp"
#include "coregraphics/ColorSpace.hpp"

TEST_CASE("Color")
{
    cg::ColorSpace colorSpace = cg::ColorSpace::deviceRGB();

    const cg::Float bgColor[] = {0.0, 0.0, 0.0, 0.0};
    cg::Color color{colorSpace, bgColor};
    CHECK(color);
    CHECK(color.retainCount() == 1);
}

TEST_CASE("ColorSpace")
{
    cg::ColorSpace colorSpace = cg::ColorSpace::deviceRGB();
    CHECK(colorSpace);
    CHECK(colorSpace.retainCount());
}
