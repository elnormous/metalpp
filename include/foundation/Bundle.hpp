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
        METALPP_PRIVATE_SEL(infoDictionary, "infoDictionary");
        
        using Object::Object;

        [[nodiscard]] static auto mainBundle() noexcept
        {
            return Bundle{objc::sendMessage<id>(cls, METALPP_SEL(mainBundle))};
        }

        Bundle() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        Bundle(const String& title) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithPath_),
                                         title.get()), adopt}
        {
        }

        [[nodiscard]] Dictionary<String, Object> infoDictionary() const noexcept
        {
            return getRetained<Dictionary<String, Object>>(METALPP_SEL(infoDictionary));
        }
    };
}

#endif
