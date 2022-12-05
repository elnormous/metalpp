#ifndef METALPP_APPKIT_SELECTORS_HPP
#define METALPP_APPKIT_SELECTORS_HPP

namespace ns
{
    namespace sel
    {
        inline const auto sharedApplication = sel_registerName("sharedApplication");
        inline const auto delegate = sel_registerName("delegate");
        inline const auto setDelegate_ = sel_registerName("setDelegate:");
        inline const auto activateIgnoringOtherApps_ = sel_registerName("activateIgnoringOtherApps:");
        inline const auto run = sel_registerName("run");
        inline const auto mainMenu = sel_registerName("mainMenu");
        inline const auto setMainMenu_ = sel_registerName("setMainMenu:");
        inline const auto helpMenu = sel_registerName("helpMenu");
        inline const auto setHelpMenu_ = sel_registerName("setHelpMenu:");
        inline const auto windowsMenu = sel_registerName("windowsMenu");
        inline const auto setWindowsMenu_ = sel_registerName("setWindowsMenu:");
        inline const auto servicesMenu = sel_registerName("servicesMenu");
        inline const auto setServicesMenu_ = sel_registerName("setServicesMenu:");

        inline const auto applicationDidFinishLaunching = sel_registerName("applicationDidFinishLaunching:");

        inline const auto screens = sel_registerName("screens");
        inline const auto mainScreen = sel_registerName("mainScreen");
        inline const auto deepestScreen = sel_registerName("deepestScreen");
        inline const auto frame = sel_registerName("frame");

        inline const auto initWithTitle_ = sel_registerName("initWithTitle:");
        inline const auto insertItem_atIndex_ = sel_registerName("insertItem:atIndex:");
        inline const auto addItem_ = sel_registerName("addItem:");
        inline const auto insertItemWithTitle_action_keyEquivalent_atIndex_ = sel_registerName("insertItemWithTitle:action:keyEquivalent:atIndex:");
        inline const auto addItemWithTitle_action_keyEquivalent_ = sel_registerName("addItemWithTitle:action:keyEquivalent:");

        inline const auto separatorItem = sel_registerName("separatorItem");
        inline const auto initWithTitle_action_keyEquivalent_ = sel_registerName("initWithTitle:action:keyEquivalent:");
        inline const auto submenu = sel_registerName("submenu");
        inline const auto setSubmenu_ = sel_registerName("setSubmenu:");
        inline const auto title = sel_registerName("title");
        inline const auto setTitle_ = sel_registerName("setTitle:");
        inline const auto isSeparatorItem = sel_registerName("isSeparatorItem");
        inline const auto keyEquivalent = sel_registerName("keyEquivalent");
        inline const auto setKeyEquivalent_ = sel_registerName("setKeyEquivalent:");
        inline const auto keyEquivalentModifierMask = sel_registerName("keyEquivalentModifierMask");
        inline const auto setKeyEquivalentModifierMask_ = sel_registerName("setKeyEquivalentModifierMask:");

        inline const auto initWithContentRect_styleMask_backing_defer_ = sel_registerName("initWithContentRect:styleMask:backing:defer:");
        inline const auto initWithContentRect_styleMask_backing_defer_screen_ = sel_registerName("initWithContentRect:styleMask:backing:defer:screen:");
        inline const auto contentView = sel_registerName("contentView");
        inline const auto setContentView_ = sel_registerName("setContentView:");
        inline const auto collectionBehavior = sel_registerName("collectionBehavior");
        inline const auto setCollectionBehavior_ = sel_registerName("setCollectionBehavior:");
        inline const auto tabbingMode = sel_registerName("tabbingMode");
        inline const auto setTabbingMode_ = sel_registerName("setTabbingMode:");
        inline const auto acceptsMouseMovedEvents = sel_registerName("acceptsMouseMovedEvents");
        inline const auto setAcceptsMouseMovedEvents_ = sel_registerName("setAcceptsMouseMovedEvents:");
        inline const auto ignoresMouseEvents = sel_registerName("ignoresMouseEvents");
        inline const auto setIgnoresMouseEvents_ = sel_registerName("setIgnoresMouseEvents:");
    }
}

#endif
