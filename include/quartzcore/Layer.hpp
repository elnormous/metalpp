#ifndef METALPP_QUARTZCORE_LAYER_HPP
#define METALPP_QUARTZCORE_LAYER_HPP

#include <dlfcn.h>
#include "../objc/Object.hpp"
#include "../corefoundation/Types.h"
#include "../foundation/String.hpp"
#include "Selectors.hpp"

namespace ca
{
    class LayerContentsFilter: public ns::String
    {
    public:
        LayerContentsFilter() = delete;
        LayerContentsFilter(const id p) noexcept: ns::String{p} {}
    };

    inline const LayerContentsFilter filterNearest{objc::sendMessage<id>(*static_cast<id*>(dlsym(RTLD_DEFAULT, "kCAFilterNearest")), ns::sel::retain)};
    inline const LayerContentsFilter filterLinear{objc::sendMessage<id>(*static_cast<id*>(dlsym(RTLD_DEFAULT, "kCAFilterLinear")), ns::sel::retain)};
    inline const LayerContentsFilter filterTrilinear{objc::sendMessage<id>(*static_cast<id*>(dlsym(RTLD_DEFAULT, "kCAFilterTrilinear")), ns::sel::retain)};

    class Layer: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("CALayer");
    public:
        Layer() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        Layer(const id p) noexcept: Object{p}
        {
        }

        [[nodiscard]] cg::Rect frame() const noexcept
        {
            return sendMessage<cg::Rect>(sel::frame);
        }

        void setFrame(cg::Rect frame) noexcept
        {
            sendMessage(sel::setFrame_, frame);
        }

        [[nodiscard]] LayerContentsFilter minificationFilter() const noexcept
        {
            return getRetained<LayerContentsFilter>(sel::minificationFilter);
        }

        void setMinificationFilter(const LayerContentsFilter& minificationFilter) noexcept
        {
            sendMessage(sel::setMinificationFilter_, static_cast<id>(minificationFilter));
        }

        [[nodiscard]] LayerContentsFilter magnificationFilter() const noexcept
        {
            return getRetained<LayerContentsFilter>(sel::magnificationFilter);
        }

        void setMagnificationFilter(const LayerContentsFilter& magnificationFilter) noexcept
        {
            sendMessage(sel::setMagnificationFilter_, static_cast<id>(magnificationFilter));
        }
    };
}

#endif
