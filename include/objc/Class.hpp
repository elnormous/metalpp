#ifndef METALPP_OBJC_CLASS_HPP
#define METALPP_OBJC_CLASS_HPP

#include <stdexcept>
#include <string>
#include <objc/objc.h>
#include <objc/runtime.h>
#include "Object.hpp"
#include "Runtime.hpp"

namespace objc
{
    class ClassError: public std::runtime_error
    {
        using runtime_error::runtime_error;
    };

    template<class ParentType = ns::Object, class Type = ParentType>
    class Class final
    {
    public:
        Class(const char* name):
            cls{objc_allocateClassPair(ParentType::cls, name, 0)}
        {
            if (!cls) throw ClassError("Failed to allocate class pair");
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

        [[nodiscard]] bool operator==(const ::Class other) const noexcept
        {
            return cls == other;
        }

        [[nodiscard]] bool operator!=(const ::Class other) const noexcept
        {
            return cls != other;
        }

        operator ::Class() const noexcept
        {
            return cls;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return cls;
        }

        void reg() noexcept
        {
            if (cls) objc_registerClassPair(cls);
        }

        [[nodiscard]] const char* getName() const noexcept
        {
            return cls ? class_getName(cls) : nullptr;
        }

        [[nodiscard]] auto isMetaClass() const noexcept
        {
            return cls ? class_isMetaClass(cls) == YES : false;
        }

        [[nodiscard]] auto getVersion() const noexcept
        {
            return cls ? class_getVersion(cls) : 0;
        }

        void setVersion(int version) noexcept
        {
            if (cls) class_setVersion(cls, version);
        }

        template<typename Ret, typename... Args>
        void addMethod(SEL name, Ret(*imp)(id, SEL, Args...), const char* types)
        {
            if (cls && !class_addMethod(cls, name, reinterpret_cast<IMP>(imp), types))
                throw ClassError("Failed to add method");
        }

        Type createInstance() const noexcept
        {
            id object = objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::Object::METALPP_SEL(alloc)), ns::Object::METALPP_SEL(init));
            return Type{object, ns::adopt};
        }
    private:
        ::Class cls = nullptr;
    };
}

#endif
