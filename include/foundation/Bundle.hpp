#ifndef METALPP_FOUNDATION_BUNDLE_HPP
#define METALPP_FOUNDATION_BUNDLE_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "Dictionary.hpp"
#include "String.hpp"

namespace ns
{
    class Bundle final: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSBundle");
    public:
        using Object::Object;

        static auto mainBundle() noexcept
        {
            return Bundle{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::mainBundle), sel::retain)};
        }

        Bundle() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        Bundle(const String& title) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithPath_,
                                         static_cast<id>(title))}
        {
        }

        Dictionary<String, Object> infoDictionary() const noexcept
        {
            return getRetained<Dictionary<String, Object>>(sel::infoDictionary);
        }
    };
}

#endif
