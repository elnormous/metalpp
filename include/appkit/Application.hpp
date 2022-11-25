#ifndef METALPP_APPKIT_APPLICATION_HPP
#define METALPP_APPKIT_APPLICATION_HPP

#include "../objc/Object.hpp"
#include "ApplicationDelegate.hpp"
#include "Selectors.hpp"

namespace ns
{
    class Application final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSApplication");
    public:
        static Application sharedApplication()
        {
            return Application{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::sharedApplication), sel::retain)};
        }

        Application() = delete;

//        [[nodiscard]] auto delegate() const noexcept
//        {
//            return getRetained<ApplicationDelegate>(sel::delegate);
//        }

        void setDelegate(const ApplicationDelegate& delegate) noexcept
        {
            sendMessage(sel::setDelegate_, static_cast<id>(delegate));
        }

        void activateIgnoringOtherApps(bool flag) noexcept
        {
            sendMessage(sel::activateIgnoringOtherApps_, flag ? YES: NO);
        }

        void run() noexcept
        {
            sendMessage(sel::run);
        }
    };
}

#endif
