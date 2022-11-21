#ifndef METALPP_FOUNDATION_STRING_HPP
#define METALPP_FOUNDATION_STRING_HPP

#include <string>
#include <string_view>
#include <objc/NSObjCRuntime.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Selectors.hpp"

namespace ns
{
    using unichar = unsigned short;

    enum class StringEncoding: NSUInteger
    {
        ASCII = 1,        // 0..127 only
        NEXTSTEP = 2,
        JapaneseEUC = 3,
        UTF8 = 4,
        ISOLatin1 = 5,
        Symbol = 6,
        NonLossyASCII = 7,
        ShiftJIS = 8,          // kCFStringEncodingDOSJapanese
        ISOLatin2 = 9,
        Unicode = 10,
        WindowsCP1251 = 11,    // Cyrillic; same as AdobeStandardCyrillic
        WindowsCP1252 = 12,    // WinLatin1
        WindowsCP1253 = 13,    // Greek
        WindowsCP1254 = 14,    // Turkish
        WindowsCP1250 = 15,    // WinLatin2
        ISO2022JP = 21,        // ISO 2022 Japanese encoding for e-mail
        MacOSRoman = 30,

        UTF16 = Unicode,      // An alias for Unicode

        UTF16BigEndian = 0x90000100,          // UTF16 encoding with explicit endianness specified
        UTF16LittleEndian = 0x94000100,       // UTF16 encoding with explicit endianness specified

        UTF32 = 0x8c000100,
        UTF32BigEndian = 0x98000100,          // UTF32 encoding with explicit endianness specified
        UTF32LittleEndian = 0x9c000100        // UTF32 encoding with explicit endianness specified
    };

    class String final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("NSString");
    public:
        String():
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        String(const id p) noexcept: Object{p} {}

        String(const char* str, const StringEncoding encoding = StringEncoding::ASCII) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc),
                                         sel::initWithCString_encoding_,
                                         str,
                                         encoding)}
        {
        }

        String(const std::string_view str, const StringEncoding encoding = StringEncoding::ASCII) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc),
                                         sel::initWithBytes_length_encoding_,
                                         str.data(),
                                         static_cast<NSUInteger>(str.length()),
                                         encoding)}
        {
        }

        [[nodiscard]] char operator[](NSUInteger index) const noexcept
        {
            return charAtIndex(index);
        }

        [[nodiscard]] char charAtIndex(const NSUInteger index) const noexcept
        {
            const auto c = sendMessage<unichar>(*this,
                                                      sel::characterAtIndex_,
                                                      index);
            return static_cast<char>(c);
        }

        [[nodiscard]] NSUInteger length() const noexcept
        {
            return sendMessage<NSUInteger>(*this, sel::length);
        }

        [[nodiscard]] const char* cString(const StringEncoding encoding = StringEncoding::ASCII) const noexcept
        {
            const auto str = sendMessage<const char*>(*this,
                                                            sel::cStringUsingEncoding_,
                                                            encoding);
            return str;
        }

        [[nodiscard]] std::string string(const StringEncoding encoding = StringEncoding::ASCII) const noexcept
        {
            const auto str = sendMessage<const char*>(*this,
                                                            sel::cStringUsingEncoding_,
                                                            encoding);
            return std::string{str};
        }

        [[nodiscard]] bool isEqualToString(const String& string) const noexcept
        {
            return sendMessage<BOOL>(*this, sel::isEqualToString_, static_cast<id>(string)) == YES;
        }
    };
}

#endif
