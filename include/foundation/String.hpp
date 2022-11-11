#ifndef METALPP_FOUNDATION_STRING_HPP
#define METALPP_FOUNDATION_STRING_HPP

#include <string>
#include <string_view>
#include <objc/NSObjCRuntime.h>
#include "../objc/Classes.hpp"
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"

namespace ns
{
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
    public:
        String():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::stringClass, objc::allocSel), objc::initSel)}
        {
        }

        String(const id p) noexcept: Object{p} {}

        String(const std::string_view str,
               const StringEncoding encoding = StringEncoding::ASCII):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(objc::stringClass, objc::allocSel),
                                         objc::initWithBytesLengthEncodingSel,
                                         str.data(),
                                         static_cast<NSUInteger>(str.length()),
                                         encoding)}
        {
        }

        char operator[](std::size_t index) const noexcept
        {
            const auto c = objc::sendMessage<unichar>(*this,
                                                      objc::characterAtIndexSel,
                                                      static_cast<NSUInteger>(index));
            return static_cast<char>(c);
        }

        std::size_t length() const noexcept
        {
            const auto length = objc::sendMessage<NSUInteger>(*this, objc::lengthSel);
            return static_cast<std::size_t>(length);
        }

        const char* cString(const StringEncoding encoding = StringEncoding::ASCII) const noexcept
        {
            const auto str = objc::sendMessage<const char*>(*this,
                                                            objc::cStringUsingEncodingSel,
                                                            encoding);
            return str;
        }

        std::string string(const StringEncoding encoding = StringEncoding::ASCII) const noexcept
        {
            const auto str = objc::sendMessage<const char*>(*this,
                                                            objc::cStringUsingEncodingSel,
                                                            encoding);
            return std::string{str};
        }
    };
}

#endif
