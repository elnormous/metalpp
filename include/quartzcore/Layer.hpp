#ifndef METALPP_QUARTZCORE_LAYER_HPP
#define METALPP_QUARTZCORE_LAYER_HPP

#include "../objc/Object.hpp"

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
    };
}

#endif
