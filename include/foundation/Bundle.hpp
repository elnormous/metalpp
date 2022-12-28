#ifndef METALPP_FOUNDATION_BUNDLE_HPP
#define METALPP_FOUNDATION_BUNDLE_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "Dictionary.hpp"
#include "String.hpp"

namespace ns
{
    class Bundle final: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSBundle");

        METALPP_PRIVATE_SEL(mainBundle, "mainBundle");
        METALPP_PRIVATE_SEL(initWithPath_, "initWithPath:");
        METALPP_PRIVATE_SEL(pathForResource_ofType_, "pathForResource:ofType:");
        METALPP_PRIVATE_SEL(pathForResource_ofType_inDirectory_, "pathForResource:ofType:inDirectory:");
        METALPP_PRIVATE_SEL(infoDictionary, "infoDictionary");
        
        using Object::Object;
        using Object::operator=;

        [[nodiscard]] static auto mainBundle() noexcept
        {
            return Bundle{objc::sendMessage<id>(cls, METALPP_SEL(mainBundle))};
        }

        Bundle() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        Bundle(const String& path) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithPath_),
                                         path.get()), adopt}
        {
        }

        [[nodiscard]] String pathForResource(const String& name, const String& ext) const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(pathForResource_ofType_), name.get(), ext.get())};
        }

        [[nodiscard]] String pathForResource(const String& name, const String& ext, const String& subpath) const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(pathForResource_ofType_inDirectory_), name.get(), ext.get(), subpath.get())};
        }

        [[nodiscard]] Dictionary<String, Object> infoDictionary() const noexcept
        {
            return Dictionary<String, Object>{sendMessage<id>(METALPP_SEL(infoDictionary))};
        }
    };
}

#endif
