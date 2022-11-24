#ifndef METALPP_APPKIT_APPLICATIONDELEGATE_HPP
#define METALPP_APPKIT_APPLICATIONDELEGATE_HPP

#include "../objc/Object.hpp"
#include "Selectors.hpp"

namespace ns
{
    static void applicationDidFinishLaunching(id self, SEL cmd, id notification)
    {
        printf("applicationDidFinishLaunching: %p %p, %p\n", self, cmd, notification);
    }

    class ApplicationDelegate: public Object
    {
        static Class createClass()
        {
            const auto result = objc_allocateClassPair(Object::cls, "ApplicationDelegate", 0);
            class_addMethod(result,
                            sel::applicationDidFinishLaunching,
                            reinterpret_cast<IMP>(applicationDidFinishLaunching),
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
    };
}

#endif
