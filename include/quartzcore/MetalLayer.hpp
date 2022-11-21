#ifndef METALPP_QUARTZCORE_METALLAYER_HPP
#define METALPP_QUARTZCORE_METALLAYER_HPP

#include "../metal/Drawable.hpp"
#include "../metal/Texture.hpp"
#include "Layer.hpp"

namespace ca
{
    class MetalLayer final: public Layer
    {
        static inline const auto cls = objc_lookUpClass("CAMetalLayer");
    public:
        MetalLayer() noexcept:
            Layer{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }
    };
}

#endif
