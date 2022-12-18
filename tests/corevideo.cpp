#include "doctest.h"
#include "corevideo/DisplayLink.hpp"

TEST_CASE("DisplayLink")
{
    const auto mainDisplayId = cv::mainDisplayID();
    CHECK(mainDisplayId);

    cv::DisplayLink displayLink{mainDisplayId};
    CHECK(displayLink);
}
