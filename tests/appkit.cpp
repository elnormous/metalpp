#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "appkit/AppKit.hpp"
#include "objc/Class.hpp"

namespace
{
    void applicationDidFinishLaunching(id, SEL, id)
    {
        ns::Application application = ns::Application::sharedApplication();
        application.stop(nullptr);
    }
}

TEST_CASE("Application")
{
    objc::Class<ns::Object> appDelegateClass{"AppDelegate"};
    appDelegateClass.addMethod(sel_registerName("applicationDidFinishLaunching:"),
                               applicationDidFinishLaunching,
                               "v@:@");
    appDelegateClass.reg();

    ns::AutoreleasePool pool;

    ns::Application application = ns::Application::sharedApplication();
    REQUIRE(application);
    CHECK(application.retainCount());
    application.activateIgnoringOtherApps(true);
    CHECK(!application.isActive());
    CHECK(!application.isHidden());
    CHECK(!application.isRunning());

    CHECK(application.setActivationPolicy(ns::ApplicationActivationPolicy::Accessory));
    CHECK(application.activationPolicy() == ns::ApplicationActivationPolicy::Accessory);

    ns::Object delegate = appDelegateClass.createInstance();
    CHECK(delegate.retainCount() == 1);
    application.setDelegate(delegate);
    CHECK(application.delegate() == delegate);

    ns::Menu mainMenu;
    application.setMainMenu(mainMenu);
    CHECK(application.mainMenu() == mainMenu);
    ns::Menu helpMenu;
    application.setHelpMenu(helpMenu);
    CHECK(application.helpMenu() == helpMenu);
    ns::Menu windowsMenu;
    application.setWindowsMenu(windowsMenu);
    CHECK(application.windowsMenu() == windowsMenu);
    ns::Menu servicesMenu;
    application.setServicesMenu(servicesMenu);
    CHECK(application.servicesMenu() == servicesMenu);

    ns::Window window{ns::Rect{0, 0, 100, 100}, ns::WindowStyleMask::Closable, ns::BackingStoreType::Buffered, false};
    window.makeKeyAndOrderFront(nullptr);

    CHECK(application.mainWindow() == nullptr);
    CHECK(application.keyWindow() == nullptr);

    application.run();
}

TEST_CASE("Array")
{
    ns::AutoreleasePool pool;

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

TEST_CASE("Event")
{
    ns::AutoreleasePool pool;

    ns::Event event;
    REQUIRE(event);
    CHECK(event.retainCount());
}

TEST_CASE("Menu")
{
    ns::AutoreleasePool pool;

    ns::Menu menu;
    REQUIRE(menu);
    CHECK(menu.retainCount());

    ns::MenuItem menuItem = menu.addItem("test", nullptr, "w");
    REQUIRE(menuItem);
    CHECK(menuItem.retainCount());
    menuItem.setTag(9);
    CHECK(menu.itemWithTitle("test") == menuItem);
    CHECK(menu.itemWithTag(9) == menuItem);

    ns::Menu menuWithTitle{"test"};
    REQUIRE(menuWithTitle);
    CHECK(menuWithTitle.retainCount());
}

TEST_CASE("MenuItem")
{
    ns::AutoreleasePool pool;

    ns::MenuItem separatorItem = ns::MenuItem::separatorItem();
    REQUIRE(separatorItem);
    CHECK(separatorItem.retainCount());
    CHECK(separatorItem.isSeparatorItem());

    ns::MenuItem menuItemWithTitle("test", nullptr, "w");
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
    menuItem.setTag(10);
    CHECK(menuItem.tag() == 10);

    ns::Menu submenu;
    menuItem.setSubmenu(submenu);
    CHECK(menuItem.submenu() == submenu);
}

TEST_CASE("Screen")
{
    ns::AutoreleasePool pool;

    ns::Array<ns::Screen> screens = ns::Screen::screens();
    REQUIRE(screens);
    CHECK(screens.retainCount());
    CHECK(screens.count());

    ns::Screen mainScreen = ns::Screen::mainScreen();
    REQUIRE(mainScreen);
    CHECK(mainScreen.retainCount());

    ns::Dictionary<ns::DeviceDescriptionKey, ns::Object> deviceDescription = mainScreen.deviceDescription();
    CHECK(deviceDescription);

    ns::Object screenNumber = deviceDescription.objectForKey("NSScreenNumber");
    CHECK(screenNumber);

    const ns::Rect frame = mainScreen.frame();
    CHECK(frame.size.width > 0);
    CHECK(frame.size.height > 0);

    ns::Screen deepestScreen = ns::Screen::deepestScreen();
    REQUIRE(deepestScreen);
    CHECK(deepestScreen.retainCount());
}

TEST_CASE("View")
{
    ns::AutoreleasePool pool;

    ns::View view;
    REQUIRE(view);
    CHECK(view.retainCount());

    CHECK(!view.superview());
    CHECK(!view.window());
    CHECK(view.autoresizingMask() == ns::AutoresizingMaskOptions::NotSizable);
    view.setAutoresizingMask(ns::AutoresizingMaskOptions::WidthSizable);
    CHECK(view.autoresizingMask() == ns::AutoresizingMaskOptions::WidthSizable);

    CHECK(!view.wantsLayer());
    view.setWantsLayer(true);
    CHECK(view.wantsLayer());

    ca::Layer layer;
    view.setLayer(layer);
    CHECK(view.layer() == layer);

    ns::View viewWithFrame{ns::Rect{0, 0, 100, 100}};
    REQUIRE(viewWithFrame);
    CHECK(viewWithFrame.retainCount());
    CHECK(viewWithFrame.frame() == ns::Rect{0, 0, 100, 100});
    viewWithFrame.setFrame(ns::Rect{10, 10, 200, 200});
    CHECK(viewWithFrame.frame() == ns::Rect{10, 10, 200, 200});

    view.addSubview(viewWithFrame);
    CHECK(viewWithFrame.superview() == view);
    viewWithFrame.removeFromSuperview();
    CHECK(!viewWithFrame.superview());
}

TEST_CASE("Window")
{
    ns::AutoreleasePool pool;

    ns::Window window{ns::Rect{0, 0, 100, 100}, ns::WindowStyleMask::Closable, ns::BackingStoreType::Buffered, false};
    REQUIRE(window);
    CHECK(window.retainCount());

    window.setTitle("title");
    CHECK(window.title().isEqualToString("title"));

    ns::View view;
    window.setContentView(view);
    CHECK(window.contentView() == view);
    CHECK(view.window() == window);

    ns::Object delegate;
    window.setDelegate(delegate);
    CHECK(window.delegate() == delegate);

    CHECK(!window.isReleasedWhenClosed());

    CHECK(window.screen());
    
    CHECK(window.collectionBehavior() == ns::WindowCollectionBehavior::Default);
    window.setCollectionBehavior(ns::WindowCollectionBehavior::Auxiliary);
    CHECK(window.collectionBehavior() == ns::WindowCollectionBehavior::Auxiliary);

    CHECK(!window.acceptsMouseMovedEvents());
    window.setAcceptsMouseMovedEvents(true);
    CHECK(window.acceptsMouseMovedEvents());

    CHECK(!window.ignoresMouseEvents());
    window.setIgnoresMouseEvents(true);
    CHECK(window.ignoresMouseEvents());

    CHECK(window.tabbingMode() == ns::WindowTabbingMode::Automatic);
    window.setTabbingMode(ns::WindowTabbingMode::Disallowed);
    CHECK(window.tabbingMode() == ns::WindowTabbingMode::Disallowed);

    window.close();

    ns::Window windowOnScreen{ns::Rect{0, 0, 100, 100}, ns::WindowStyleMask::Closable, ns::BackingStoreType::Buffered, false, ns::Screen::mainScreen()};
    REQUIRE(windowOnScreen);
    CHECK(windowOnScreen.retainCount());

    pool.drain();
    CHECK(window.retainCount() == 1);
}
