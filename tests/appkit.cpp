#include "doctest.h"
#include "appkit/Application.hpp"

TEST_CASE("Application")
{
    ns::Application application;
    REQUIRE(application);
    REQUIRE(application.retainCount());
    application.activateIgnoringOtherApps(true);
    //application.run();
}
