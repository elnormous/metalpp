#ifndef METALPP_FOUNDATION_ERROR_HPP
#define METALPP_FOUNDATION_ERROR_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"
#include "String.hpp"

namespace ns
{
    class Error final: public ns::Object
    {
    public:
        Error(const id p) noexcept: Object{p} {}

        Error(const ns::String& domain, const NSInteger& code) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::error, ns::sel::alloc),
                                         sel::initWithDomain_code_userInfo_,
                                         static_cast<id>(domain),
                                         code,
                                         nil)}
        {
        }

        NSInteger code() const noexcept
        {
            return objc::sendMessage<NSInteger>(*this, sel::code);
        }

        ns::String domain() const noexcept
        {
            const id domain = objc::sendMessage<id>(*this, sel::domain);
            return ns::String{objc::sendMessage<id>(domain, ns::sel::retain)};
        }

        ns::String localizedDescription() const noexcept
        {
            const id localizedDescription = objc::sendMessage<id>(*this, sel::localizedDescription);
            return ns::String{objc::sendMessage<id>(localizedDescription, ns::sel::retain)};
        }
    };
}

#endif
