#ifndef METALPP_APPKIT_RUNNINGAPPLICATION_HPP
#define METALPP_APPKIT_RUNNINGAPPLICATION_HPP

#include "../objc/Runtime.hpp"

namespace ns
{
    enum class ApplicationActivationPolicy: ns::Integer
    {
        /* The application is an ordinary app that appears in the Dock and may have a user interface.  This is the default for bundled apps, unless overridden in the Info.plist. */
        Regular,

        /* The application does not appear in the Dock and does not have a menu bar, but it may be activated programmatically or by clicking on one of its windows.  This corresponds to LSUIElement=1 in the Info.plist. */
        Accessory,

        /* The application does not appear in the Dock and may not create windows or be activated.  This corresponds to LSBackgroundOnly=1 in the Info.plist.  This is also the default for unbundled executables that do not have Info.plists. */
        Prohibited
    };
}

#endif
