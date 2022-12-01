#ifndef METALPP_OBJC_CLASS_HPP
#define METALPP_OBJC_CLASS_HPP

#include <string>
#include <objc/objc.h>
#include <objc/runtime.h>

namespace objc
{
    template <class T>
    class Class final
    {
    public:
        Class(const char* name) noexcept:
            cls{objc_allocateClassPair(T::cls, name, 0)}
        {
        }

        Class(const std::string& name) noexcept:
            Class{name.c_str()}
        {
        }

        ~Class()
        {
            if (cls) objc_disposeClassPair(cls);
        }

        Class(Class&& other) noexcept:
            cls{other.cls}
        {
            other.cls = nil;
        }

        Class& operator=(Class&& other) noexcept
        {
            if (&other == this) return *this;
            cls = other.cls;
            other.cls = nil;
            return *this;
        }

        void reg() noexcept
        {
            if (cls) objc_registerClassPair(cls);
        }

        const char* getName() const noexcept
        {
            return cls ? class_getName(cls) : nullptr;
        }

        auto isMetaClass() const noexcept
        {
            return cls ? class_isMetaClass(cls) == YES : false;
        }

        auto getVersion() const noexcept
        {
            return cls ? class_getVersion(cls) : 0;
        }

        void setVersion(int version) noexcept
        {
            if (cls) class_setVersion(cls, version);
        }

    private:
        ::Class cls = nullptr;
    };
}

#endif
