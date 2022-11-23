#ifndef METALPP_QUARTZCORE_SELECTORS_HPP
#define METALPP_QUARTZCORE_SELECTORS_HPP

namespace ca
{
    namespace sel
    {
        inline const auto frame = sel_registerName("frame");
        inline const auto setFrame_ = sel_registerName("setFrame:");
        inline const auto minificationFilter = sel_registerName("minificationFilter");
        inline const auto setMinificationFilter_ = sel_registerName("setMinificationFilter:");
        inline const auto magnificationFilter = sel_registerName("magnificationFilter");
        inline const auto setMagnificationFilter_ = sel_registerName("setMagnificationFilter:");
    }
}

#endif
