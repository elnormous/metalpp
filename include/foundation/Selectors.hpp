#ifndef METALPP_FOUNDATION_SELECTORS_HPP
#define METALPP_FOUNDATION_SELECTORS_HPP

namespace ns
{
    namespace sel
    {
        inline const auto initWithObjects_ = sel_registerName("initWithObjects:");
        inline const auto initWithObjects_count_ = sel_registerName("initWithObjects:count:");
        inline const auto objectAtIndex_ = sel_registerName("objectAtIndex:");
        inline const auto objectAtIndexedSubscript_ = sel_registerName("objectAtIndexedSubscript:");
        inline const auto setObject_atIndexedSubscript_ = sel_registerName("setObject:atIndexedSubscript:");
        inline const auto count = sel_registerName("count");

        inline const auto initWithObjects_forKeys_ = sel_registerName("initWithObjects:forKeys:");
        inline const auto initWithObjectsAndKeys_ = sel_registerName("initWithObjectsAndKeys:");
        inline const auto allKeys = sel_registerName("allKeys");
        inline const auto allKeysForObject_ = sel_registerName("allKeysForObject:");
        inline const auto allValues = sel_registerName("allValues");
        inline const auto objectForKey_ = sel_registerName("objectForKey:");

        inline const auto drain = sel_registerName("drain");

        inline const auto code = sel_registerName("code");
        inline const auto domain = sel_registerName("domain");
        inline const auto localizedDescription = sel_registerName("localizedDescription");

        inline const auto initWithBytes_length_encoding_ = sel_registerName("initWithBytes:length:encoding:");
        inline const auto initWithCString_encoding_ = sel_registerName("initWithCString:encoding:");

        inline const auto length = sel_registerName("length");
        inline const auto characterAtIndex_ = sel_registerName("characterAtIndex:");
        inline const auto cStringUsingEncoding_ = sel_registerName("cStringUsingEncoding:");
        inline const auto isEqualToString_ = sel_registerName("isEqualToString:");
    }
}

#endif
