#include "doctest.h"
#include "appkit/Application.hpp"
#include "appkit/ApplicationDelegate.hpp"
#include "appkit/Menu.hpp"
#include "appkit/MenuItem.hpp"
#include "appkit/Screen.hpp"

TEST_CASE("Application")
{
    ns::Application application = ns::Application::sharedApplication();
    REQUIRE(application);
    CHECK(application.retainCount());
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
    ns::Array<ns::Object> emptyArray;
    REQUIRE(emptyArray);
    CHECK(emptyArray.retainCount());

    ns::Object object;
    ns::Array<ns::Object> filledArray = {object};
    REQUIRE(filledArray);
    CHECK(filledArray.retainCount());
    CHECK(filledArray.count() == 1);
    CHECK(filledArray.objectAtIndex(0) == object);
    CHECK(filledArray[0] == object);
}

TEST_CASE("Menu")
{
    ns::Menu menu;
    REQUIRE(menu);
    CHECK(menu.retainCount());

    ns::MenuItem menuItem = menu.addItem("test", nil, "w");
    REQUIRE(menuItem);
    CHECK(menuItem.retainCount());

    ns::Menu menuWithTitle{"test"};
    REQUIRE(menuWithTitle);
    CHECK(menuWithTitle.retainCount());
}

TEST_CASE("MenuItem")
{
    ns::MenuItem separatorItem = ns::MenuItem::separatorItem();
    REQUIRE(separatorItem);
    CHECK(separatorItem.retainCount());
    CHECK(separatorItem.isSeparatorItem());

    ns::MenuItem menuItemWithTitle("test", nil, "w");
    REQUIRE(menuItemWithTitle);
    CHECK(menuItemWithTitle.retainCount());
    CHECK(menuItemWithTitle.title().isEqualToString("test"));
    menuItemWithTitle.setTitle("title");
    CHECK(menuItemWithTitle.title().isEqualToString("title"));
    CHECK(!menuItemWithTitle.isSeparatorItem());
    CHECK(menuItemWithTitle.keyEquivalent().isEqualToString("w"));
    menuItemWithTitle.setKeyEquivalent("a");
    CHECK(menuItemWithTitle.keyEquivalent().isEqualToString("a"));

    ns::MenuItem menuItem;
    REQUIRE(menuItem);
    CHECK(menuItem.retainCount());
    menuItem.setKeyEquivalentModifierMask(ns::EventModifierFlags::Command | ns::EventModifierFlags::Option);
    CHECK(menuItem.keyEquivalentModifierMask() == (ns::EventModifierFlags::Command | ns::EventModifierFlags::Option));

    ns::Menu submenu;
    menuItem.setSubmenu(submenu);
    CHECK(menuItem.submenu() == submenu);
}

TEST_CASE("Screen")
{
    ns::Array<ns::Screen> screens = ns::Screen::screens();
    REQUIRE(screens);
    CHECK(screens.retainCount());
    CHECK(screens.count());

    ns::Screen mainScreen = ns::Screen::mainScreen();
    REQUIRE(mainScreen);
    CHECK(mainScreen.retainCount());

    const cg::Rect frame = mainScreen.frame();
    CHECK(frame.size.width > 0);
    CHECK(frame.size.height > 0);

    ns::Screen deepestScreen = ns::Screen::deepestScreen();
    REQUIRE(deepestScreen);
    CHECK(deepestScreen.retainCount());
}
