#ifndef METALPP_FOUNDATION_ERROR_HPP
#define METALPP_FOUNDATION_ERROR_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Dictionary.hpp"
#include "Selectors.hpp"
#include "String.hpp"

namespace ns
{
    class Error final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("NSError");
    public:
        Error(const id p) noexcept: Object{p} {}

        Error(const ns::String& domain, const NSInteger& code) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc),
                                   sel::initWithDomain_code_userInfo_,
                                   static_cast<id>(domain),
                                   code,
                                   nil)}
        {
        }

        Error(const ns::String& domain, const NSInteger& code, const ns::Dictionary<ns::String, ns::Object>& userInfo) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc),
                                   sel::initWithDomain_code_userInfo_,
                                   static_cast<id>(domain),
                                   code,
                                   static_cast<id>(userInfo))}
        {
        }

        NSInteger code() const noexcept
        {
            return sendMessage<NSInteger>(sel::code);
        }

        ns::String domain() const noexcept
        {
            return getRetained<ns::String>(sel::domain);
        }

        ns::Dictionary<ns::String, ns::Object> userInfo() const noexcept
        {
            return getRetained<ns::Dictionary<ns::String, ns::Object>>(sel::userInfo);
        }

        ns::String localizedDescription() const noexcept
        {
            return getRetained<ns::String>(sel::localizedDescription);
        }
    };
}

#endif
