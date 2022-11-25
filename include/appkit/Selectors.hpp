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

        inline const auto applicationDidFinishLaunching = sel_registerName("applicationDidFinishLaunching:");

        inline const auto screens = sel_registerName("screens");
        inline const auto mainScreen = sel_registerName("mainScreen");
        inline const auto deepestScreen = sel_registerName("deepestScreen");
        inline const auto frame = sel_registerName("frame");
    }
}

#endif
