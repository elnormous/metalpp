#ifndef METALPP_APPKIT_APPLICATIONDELEGATE_HPP
#define METALPP_APPKIT_APPLICATIONDELEGATE_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Selectors.hpp"

namespace ns
{
    class ApplicationDelegate: public Object
    {
        static Class createClass()
        {
            const auto result = objc_allocateClassPair(Object::cls, "ApplicationDelegate", 0);
            class_addMethod(result,
                            sel::applicationDidFinishLaunching,
                            reinterpret_cast<IMP>(applicationDidFinishLaunchingPriv),
                            "v@:@");
            return result;
        }

        static inline const auto cls = createClass();
    public:
        ApplicationDelegate() noexcept:
            Object{objc::sendMessage<id>(class_createInstance(cls, sizeof(ApplicationDelegate*)), sel::init)}
        {
            void* dest = object_getIndexedIvars(*this);
            void* ptr = this;
            std::memcpy(dest, &ptr, sizeof(ApplicationDelegate*));
        }

        ApplicationDelegate(const ApplicationDelegate&) = delete;
        ApplicationDelegate(ApplicationDelegate&&) = delete;
        ApplicationDelegate& operator=(const ApplicationDelegate&) = delete;
        ApplicationDelegate& operator=(ApplicationDelegate&&) = delete;

        virtual void applicationDidFinishLaunching([[maybe_unused]] id notification) {}

    private:
        static void applicationDidFinishLaunchingPriv(id self, [[maybe_unused]] SEL cmd, id notification)
        {
            const void* dest = object_getIndexedIvars(self);
            ApplicationDelegate* ptr;
            memcpy(&ptr, dest, sizeof(ApplicationDelegate*));
            ptr->applicationDidFinishLaunching(notification);
        }
    };
}

#endif
