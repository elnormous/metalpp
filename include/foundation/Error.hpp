#ifndef METALPP_FOUNDATION_ERROR_HPP
#define METALPP_FOUNDATION_ERROR_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "String.hpp"

namespace ns
{
    class Error final: public ns::Object
    {
    public:
        Error(const id p) noexcept: Object{p} {}

        NSInteger code() const noexcept
        {
            return objc::sendMessage<NSInteger>(*this, objc::sel::code);
        }

        ns::String domain() const noexcept
        {
            const id domain = objc::sendMessage<id>(*this, objc::sel::domain);
            return ns::String{objc::sendMessage<id>(domain, objc::sel::retain)};
        }

        ns::String localizedDescription() const noexcept
        {
            const id localizedDescription = objc::sendMessage<id>(*this, objc::sel::localizedDescription);
            return ns::String{objc::sendMessage<id>(localizedDescription, objc::sel::retain)};
        }
    };
}

#endif
