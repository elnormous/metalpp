#include "doctest.h"
#include "coregraphics/CoreGraphics.hpp"

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

TEST_CASE("Float")
{
    CGFloat f = 5.0;
    cg::Float r = f;
    CHECK(r == f);
    CHECK(r == 5.0);
}
