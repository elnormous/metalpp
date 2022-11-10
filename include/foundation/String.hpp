#ifndef METALPP_FOUNDATION_STRING_HPP
#define METALPP_FOUNDATION_STRING_HPP

#include <string>
#include <string_view>
#include <objc/NSObjCRuntime.h>
#include "../objc/Object.hpp"

namespace ns
{
    enum class StringEncoding: NSUInteger
    {
        ASCIIStringEncoding = 1,        // 0..127 only
        NEXTSTEPStringEncoding = 2,
        JapaneseEUCStringEncoding = 3,
        UTF8StringEncoding = 4,
        ISOLatin1StringEncoding = 5,
        SymbolStringEncoding = 6,
        NonLossyASCIIStringEncoding = 7,
        ShiftJISStringEncoding = 8,          // kCFStringEncodingDOSJapanese
        ISOLatin2StringEncoding = 9,
        UnicodeStringEncoding = 10,
        WindowsCP1251StringEncoding = 11,    // Cyrillic; same as AdobeStandardCyrillic
        WindowsCP1252StringEncoding = 12,    // WinLatin1
        WindowsCP1253StringEncoding = 13,    // Greek
        WindowsCP1254StringEncoding = 14,    // Turkish
        WindowsCP1250StringEncoding = 15,    // WinLatin2
        ISO2022JPStringEncoding = 21,        // ISO 2022 Japanese encoding for e-mail
        MacOSRomanStringEncoding = 30,

        UTF16StringEncoding = NSUnicodeStringEncoding,      // An alias for NSUnicodeStringEncoding

        UTF16BigEndianStringEncoding = 0x90000100,          // NSUTF16StringEncoding encoding with explicit endianness specified
        UTF16LittleEndianStringEncoding = 0x94000100,       // NSUTF16StringEncoding encoding with explicit endianness specified

        UTF32StringEncoding = 0x8c000100,
        UTF32BigEndianStringEncoding = 0x98000100,          // NSUTF32StringEncoding encoding with explicit endianness specified
        UTF32LittleEndianStringEncoding = 0x9c000100        // NSUTF32StringEncoding encoding with explicit endianness specified
    };

    class String final: public ns::Object
    {
        inline static const Class cls = objc_lookUpClass("NSString");

        inline static const auto allocSel = sel_registerName("alloc");
        inline static const auto initWithBytesLengthEncodingSel = sel_registerName("initWithBytes:length:encoding:");
        inline static const auto lengthSel = sel_registerName("length");
        inline static const auto characterAtIndexSel = sel_registerName("characterAtIndex:");
        inline static const auto cStringUsingEncodingSel = sel_registerName("cStringUsingEncoding:");

    public:
        using Object::Object;

        String(const std::string_view str,
               const StringEncoding encoding = StringEncoding::ASCIIStringEncoding):
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel),
                                         initWithBytesLengthEncodingSel,
                                         str.data(),
                                         static_cast<NSUInteger>(str.length()),
                                         encoding), false}
        {
        }

        char operator[](std::size_t index) const noexcept
        {
            unichar c = objc::sendMessage<unichar>(*this,
                                                   characterAtIndexSel,
                                                   static_cast<NSUInteger>(index));
            return static_cast<char>(c);
        }

        std::size_t length() const noexcept
        {
            NSUInteger len = objc::sendMessage<NSUInteger>(*this, lengthSel);
            return static_cast<std::size_t>(len);
        }

        const char* cString(const StringEncoding encoding = StringEncoding::ASCIIStringEncoding) const noexcept
        {
            const char* str = objc::sendMessage<const char*>(*this,
                                                             cStringUsingEncodingSel,
                                                             encoding);
            return str;
        }

        std::string string(const StringEncoding encoding = StringEncoding::ASCIIStringEncoding) const noexcept
        {
            const char* str = objc::sendMessage<const char*>(*this,
                                                             cStringUsingEncodingSel,
                                                             encoding);
            return std::string{str};
        }
    };
}

#endif
