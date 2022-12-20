#ifndef METALPP_FOUNDATION_STRING_HPP
#define METALPP_FOUNDATION_STRING_HPP

#include <string>
#include <string_view>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"

namespace ns
{
    using unichar = unsigned short;

    enum class StringEncoding: UInteger
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

    class String: public Object
    {
    public:
        static constexpr bool copying = true;
        
        METALPP_PRIVATE_CLS("NSString");

        METALPP_PRIVATE_SEL(initWithBytes_length_encoding_, "initWithBytes:length:encoding:");
        METALPP_PRIVATE_SEL(initWithCString_encoding_, "initWithCString:encoding:");
        METALPP_PRIVATE_SEL(length, "length");
        METALPP_PRIVATE_SEL(characterAtIndex_, "characterAtIndex:");
        METALPP_PRIVATE_SEL(cStringUsingEncoding_, "cStringUsingEncoding:");
        METALPP_PRIVATE_SEL(isEqualToString_, "isEqualToString:");
        METALPP_PRIVATE_SEL(stringByAppendingString_, "stringByAppendingString:");
        
        using Object::Object;

        String():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        String(const char* str, const StringEncoding encoding = StringEncoding::ASCII) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithCString_encoding_),
                                         str,
                                         encoding), adopt}
        {
        }

        String(const std::string_view str, const StringEncoding encoding = StringEncoding::ASCII) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithBytes_length_encoding_),
                                         str.data(),
                                         static_cast<UInteger>(str.length()),
                                         encoding), adopt}
        {
        }

        [[nodiscard]] auto charAtIndex(const UInteger index) const noexcept
        {
            const auto c = sendMessage<unichar>(METALPP_SEL(characterAtIndex_), index);
            return static_cast<char>(c);
        }

        [[nodiscard]] auto operator[](UInteger index) const noexcept
        {
            return charAtIndex(index);
        }

        [[nodiscard]] auto length() const noexcept
        {
            return sendMessage<UInteger>(METALPP_SEL(length));
        }

        [[nodiscard]] auto cString(const StringEncoding encoding = StringEncoding::ASCII) const noexcept
        {
            const auto str = sendMessage<const char*>(METALPP_SEL(cStringUsingEncoding_), encoding);
            return str;
        }

        [[nodiscard]] auto string(const StringEncoding encoding = StringEncoding::ASCII) const noexcept
        {
            const auto str = sendMessage<const char*>(METALPP_SEL(cStringUsingEncoding_), encoding);
            return std::string{str};
        }

        [[nodiscard]] auto isEqualToString(const String& string) const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isEqualToString_), string.get()) == YES;
        }

        [[nodiscard]] auto stringByAppendingString(const String& string) const noexcept
        {
            return String{sendMessage<id>(METALPP_SEL(stringByAppendingString_), string.get())};
        }

        [[nodiscard]] auto operator+(const String& string) const noexcept
        {
            return stringByAppendingString(string);
        }
    };
}

#endif
