#include "doctest.h"
#include "appkit/Application.hpp"
#include "appkit/ApplicationDelegate.hpp"
#include "appkit/Menu.hpp"
#include "appkit/Screen.hpp"

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

TEST_CASE("Array")
{
    ns::Array<ns::Object> array;
}

TEST_CASE("Screen")
{
    ns::Array<ns::Screen> screens = ns::Screen::screens();
    REQUIRE(screens);
    REQUIRE(screens.retainCount());
    CHECK(screens.count());

    ns::Screen mainScreen = ns::Screen::mainScreen();
    REQUIRE(mainScreen);
    REQUIRE(mainScreen.retainCount());

    const cg::Rect frame = mainScreen.frame();
    CHECK(frame.size.width > 0);
    CHECK(frame.size.height > 0);

    ns::Screen deepestScreen = ns::Screen::deepestScreen();
    REQUIRE(deepestScreen);
    REQUIRE(deepestScreen.retainCount());
}
