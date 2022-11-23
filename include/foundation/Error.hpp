#ifndef METALPP_FOUNDATION_ERROR_HPP
#define METALPP_FOUNDATION_ERROR_HPP

#include "../objc/Object.hpp"
#include "../objc/Runtime.hpp"
#include "../objc/Selectors.hpp"
#include "Dictionary.hpp"
#include "Selectors.hpp"
#include "String.hpp"

namespace ns
{
    class Error: public Object
    {
        static inline const auto cls = objc_lookUpClass("NSError");
    public:
        using Object::Object;
        Error() = delete;

        Error(const String& domain, const Integer& code) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithDomain_code_userInfo_,
                                         static_cast<id>(domain),
                                         code,
                                         nil)}
        {
        }

        Error(const String& domain, const Integer& code, const Dictionary<String, Object>& userInfo) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithDomain_code_userInfo_,
                                         static_cast<id>(domain),
                                         code,
                                         static_cast<id>(userInfo))}
        {
        }

        Integer code() const noexcept
        {
            return sendMessage<Integer>(sel::code);
        }

        String domain() const noexcept
        {
            return getRetained<String>(sel::domain);
        }

        Dictionary<String, Object> userInfo() const noexcept
        {
            return getRetained<Dictionary<String, Object>>(sel::userInfo);
        }

        String localizedDescription() const noexcept
        {
            return getRetained<String>(sel::localizedDescription);
        }
    };
}

#endif
