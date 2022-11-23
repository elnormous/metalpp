#ifndef METALPP_QUARTZCORE_SELECTORS_HPP
#define METALPP_QUARTZCORE_SELECTORS_HPP

namespace ca
{
    namespace sel
    {
        inline const auto anchorPoint = sel_registerName("anchorPoint");
        inline const auto setAnchorPoint_ = sel_registerName("setAnchorPoint:");
        inline const auto frame = sel_registerName("frame");
        inline const auto setFrame_ = sel_registerName("setFrame:");
        inline const auto masksToBounds = sel_registerName("masksToBounds");
        inline const auto setMasksToBounds_ = sel_registerName("setMasksToBounds:");
        inline const auto minificationFilter = sel_registerName("minificationFilter");
        inline const auto setMinificationFilter_ = sel_registerName("setMinificationFilter:");
        inline const auto magnificationFilter = sel_registerName("magnificationFilter");
        inline const auto setMagnificationFilter_ = sel_registerName("setMagnificationFilter:");
        inline const auto autoresizingMask = sel_registerName("autoresizingMask");
        inline const auto setAutoresizingMask_ = sel_registerName("setAutoresizingMask:");
        inline const auto edgeAntialiasingMask = sel_registerName("edgeAntialiasingMask");
        inline const auto setEdgeAntialiasingMask_ = sel_registerName("setEdgeAntialiasingMask:");

        inline const auto pixelFormat = sel_registerName("pixelFormat");
        inline const auto setPixelFormat_ = sel_registerName("setPixelFormat:");
        inline const auto framebufferOnly = sel_registerName("framebufferOnly");
        inline const auto setFramebufferOnly_ = sel_registerName("setFramebufferOnly:");
        inline const auto drawableSize = sel_registerName("drawableSize");
        inline const auto setDrawableSize_ = sel_registerName("setDrawableSize:");
        inline const auto nextDrawable = sel_registerName("nextDrawable");
        inline const auto presentsWithTransaction = sel_registerName("presentsWithTransaction");
        inline const auto setPresentsWithTransaction_ = sel_registerName("setPresentsWithTransaction:");

        inline const auto layer = sel_registerName("layer");
    }
}

#endif
