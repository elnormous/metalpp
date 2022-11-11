#ifndef METALPP_FOUNDATION_SELECTORS_HPP
#define METALPP_FOUNDATION_SELECTORS_HPP

namespace ns
{
    namespace sel
    {
        inline const auto objectAtIndexedSubscript_ = sel_registerName("objectAtIndexedSubscript:");
        inline const auto setObject_atIndexedSubscript_ = sel_registerName("setObject:atIndexedSubscript:");

        inline const auto drain = sel_registerName("drain");

        inline const auto code = sel_registerName("code");
        inline const auto domain = sel_registerName("domain");
        inline const auto localizedDescription = sel_registerName("localizedDescription");

        inline const auto initWithBytes_length_encoding_ = sel_registerName("initWithBytes:length:encoding:");
        inline const auto length = sel_registerName("length");
        inline const auto characterAtIndex_ = sel_registerName("characterAtIndex:");
        inline const auto cStringUsingEncoding_ = sel_registerName("cStringUsingEncoding:");
    }
}

#endif
