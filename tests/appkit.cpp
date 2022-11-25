#include "doctest.h"
#include "appkit/Application.hpp"

TEST_CASE("Application")
{
    ns::Application application = ns::Application::sharedApplication();
    REQUIRE(application);
    REQUIRE(application.retainCount());
    application.activateIgnoringOtherApps(true);
    //application.run();
}

TEST_CASE("ApplicationDelegate")
{
    ns::ApplicationDelegate delegate;
}

class ApplicationDelegate: public ns::ApplicationDelegate
{

};

TEST_CASE("ApplicationDelegate")
{
    ApplicationDelegate delegate;
}
