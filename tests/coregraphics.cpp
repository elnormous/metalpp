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
    CGFloat test = 5.0;
    cg::Float r = test;
    CHECK(r == r);
    CHECK_FALSE(r != r);
    CHECK(r == test);
    CHECK_FALSE(r != test);
    CHECK(r == 5.0);
}

TEST_CASE("Point")
{
    CGPoint test = CGPointMake(5.0, 6.0);
    cg::Point r = test;
    CHECK(r == r);
    CHECK_FALSE(r != r);
    CHECK(r == test);
    CHECK_FALSE(r != test);
    CHECK(r.x == 5.0);
    CHECK(r.y == 6.0);
}

TEST_CASE("Size")
{
    CGSize test = CGSizeMake(5.0, 6.0);
    cg::Size r = test;
    CHECK(r == r);
    CHECK_FALSE(r != r);
    CHECK(r == test);
    CHECK_FALSE(r != test);
    CHECK(r.width == 5.0);
    CHECK(r.height == 6.0);
}

TEST_CASE("Vector")
{
    CGVector test = CGVectorMake(5.0, 6.0);
    cg::Vector r = test;
    CHECK(r == r);
    CHECK_FALSE(r != r);
    CHECK(r == test);
    CHECK_FALSE(r != test);
    CHECK(r.dx == 5.0);
    CHECK(r.dy == 6.0);
}

TEST_CASE("Rect")
{
    CGRect test = CGRectMake(5.0, 6.0, 7.0, 8.0);
    cg::Rect r = test;
    CHECK(r == r);
    CHECK_FALSE(r != r);
    CHECK(r == test);
    CHECK_FALSE(r != test);
    CHECK(r.origin.x == 5.0);
    CHECK(r.origin.y == 6.0);
    CHECK(r.size.width == 7.0);
    CHECK(r.size.height == 8.0);
}
