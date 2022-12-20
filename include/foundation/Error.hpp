#ifndef METALPP_FOUNDATION_ERROR_HPP
#define METALPP_FOUNDATION_ERROR_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "Dictionary.hpp"
#include "String.hpp"

namespace ns
{
    class Error: public Object
    {
    public:
        static constexpr bool copying = true;
        
        METALPP_PRIVATE_CLS("NSError");

        METALPP_PRIVATE_SEL(initWithDomain_code_userInfo_, "initWithDomain:code:userInfo:");
        METALPP_PRIVATE_SEL(code, "code");
        METALPP_PRIVATE_SEL(domain, "domain");
        METALPP_PRIVATE_SEL(userInfo, "userInfo");
        METALPP_PRIVATE_SEL(localizedDescription, "localizedDescription");
        
        using Object::Object;
        Error() = delete;

        Error(const String& domain, const Integer& code) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithDomain_code_userInfo_),
                                         domain.get(),
                                         code,
                                         nil), adopt}
        {
        }

        Error(const String& domain, const Integer& code, const Dictionary<String, Object>& userInfo) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithDomain_code_userInfo_),
                                         domain.get(),
                                         code,
                                         userInfo.get()), adopt}
        {
        }

        [[nodiscard]] Integer code() const noexcept
        {
            return sendMessage<Integer>(METALPP_SEL(code));
        }

        [[nodiscard]] String domain() const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(domain))};
        }

        [[nodiscard]] Dictionary<String, Object> userInfo() const noexcept
        {
            return Dictionary<String, Object>{sendMessage<id>(METALPP_SEL(userInfo))};
        }

        [[nodiscard]] String localizedDescription() const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(localizedDescription))};
        }
    };
}

#endif
