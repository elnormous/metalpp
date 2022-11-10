#ifndef METALPP_FOUNDATION_ERROR_HPP
#define METALPP_FOUNDATION_ERROR_HPP

#include "../objc/Object.hpp"
#include "String.hpp"

namespace ns
{
    class Error final: public ns::Object
    {
        inline static const auto codeSel = sel_registerName("code");
        inline static const auto domainSel = sel_registerName("domain");
        inline static const auto localizedDescriptionSel = sel_registerName("localizedDescription");

    public:
        Error(const id p) noexcept: Object{p} {}

        NSInteger code() const noexcept
        {
            return objc::sendMessage<NSInteger>(*this, codeSel);
        }

        ns::String domain() const noexcept
        {
            const id domain = objc::sendMessage<id>(*this, domainSel);
            return ns::String{objc::sendMessage<id>(domain, retainSel)};
        }

        ns::String localizedDescription() const noexcept
        {
            const id localizedDescription = objc::sendMessage<id>(*this, localizedDescriptionSel);
            return ns::String{objc::sendMessage<id>(localizedDescription, retainSel)};
        }
    };
}

#endif
