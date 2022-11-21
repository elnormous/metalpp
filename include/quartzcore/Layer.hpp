#ifndef METALPP_QUARTZCORE_LAYER_HPP
#define METALPP_QUARTZCORE_LAYER_HPP

#include <dlfcn.h>
#include "../objc/Object.hpp"
#include "../corefoundation/Types.h"
#include "Selectors.hpp"

namespace ca
{
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
            return objc::sendMessage<cg::Rect>(*this, sel::frame);
        }

        void setFrame(cg::Rect frame) noexcept
        {
            objc::sendMessage(*this, sel::setFrame_, frame);
        }
    };

    namespace detail
    {
        inline const auto filterNearest = static_cast<id>(dlsym(RTLD_DEFAULT, "kCAFilterNearest"));
        inline const auto filterLinear = static_cast<id>(dlsym(RTLD_DEFAULT, "kCAFilterLinear"));
        inline const auto filterTrilinear = static_cast<id>(dlsym(RTLD_DEFAULT, "kCAFilterTrilinear"));
    }
}

#endif
