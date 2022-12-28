#ifndef METALPP_QUARTZCORE_LAYER_HPP
#define METALPP_QUARTZCORE_LAYER_HPP

#include <dlfcn.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../corefoundation/Types.hpp"
#include "../coregraphics/Color.hpp"
#include "../foundation/String.hpp"

namespace ca
{
    enum class AutoresizingMask: unsigned int
    {
        NotSizable    = 0,
        MinXMargin    = 1U << 0,
        WidthSizable  = 1U << 1,
        MaxXMargin    = 1U << 2,
        MinYMargin    = 1U << 3,
        HeightSizable = 1U << 4,
        MaxYMargin    = 1U << 5
    };

    [[nodiscard]] inline constexpr AutoresizingMask operator&(const AutoresizingMask a, const AutoresizingMask b) noexcept
    {
        return static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) & static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    [[nodiscard]] inline constexpr AutoresizingMask operator|(const AutoresizingMask a, const AutoresizingMask b) noexcept
    {
        return static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) | static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    [[nodiscard]] inline constexpr AutoresizingMask operator^(const AutoresizingMask a, const AutoresizingMask b) noexcept
    {
        return static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) ^ static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    [[nodiscard]] inline constexpr AutoresizingMask operator~(const AutoresizingMask a) noexcept
    {
        return static_cast<AutoresizingMask>(~static_cast<std::underlying_type_t<AutoresizingMask>>(a));
    }
    inline constexpr AutoresizingMask& operator&=(AutoresizingMask& a, const AutoresizingMask b) noexcept
    {
        return a = static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) & static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    inline constexpr AutoresizingMask& operator|=(AutoresizingMask& a, const AutoresizingMask b) noexcept
    {
        return a = static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) | static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    inline constexpr AutoresizingMask& operator^=(AutoresizingMask& a, const AutoresizingMask b) noexcept
    {
        return a = static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) ^ static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }

    enum class EdgeAntialiasingMask: unsigned int
    {
        None          = 0,
        LeftEdge      = 1U << 0,      /* Minimum X edge. */
        RightEdge     = 1U << 1,      /* Maximum X edge. */
        BottomEdge    = 1U << 2,      /* Minimum Y edge. */
        TopEdge       = 1U << 3,      /* Maximum Y edge. */
    };
    inline constexpr EdgeAntialiasingMask operator&(const EdgeAntialiasingMask a, const EdgeAntialiasingMask b) noexcept
    {
        return static_cast<EdgeAntialiasingMask>(static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a) & static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(b));
    }
    inline constexpr EdgeAntialiasingMask operator|(const EdgeAntialiasingMask a, const EdgeAntialiasingMask b) noexcept
    {
        return static_cast<EdgeAntialiasingMask>(static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a) | static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(b));
    }
    inline constexpr EdgeAntialiasingMask operator^(const EdgeAntialiasingMask a, const EdgeAntialiasingMask b) noexcept
    {
        return static_cast<EdgeAntialiasingMask>(static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a) ^ static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(b));
    }
    inline constexpr EdgeAntialiasingMask operator~(const EdgeAntialiasingMask a) noexcept
    {
        return static_cast<EdgeAntialiasingMask>(~static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a));
    }
    inline constexpr EdgeAntialiasingMask& operator&=(EdgeAntialiasingMask& a, const EdgeAntialiasingMask b) noexcept
    {
        return a = static_cast<EdgeAntialiasingMask>(static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a) & static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(b));
    }
    inline constexpr EdgeAntialiasingMask& operator|=(EdgeAntialiasingMask& a, const EdgeAntialiasingMask b) noexcept
    {
        return a = static_cast<EdgeAntialiasingMask>(static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a) | static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(b));
    }
    inline constexpr EdgeAntialiasingMask& operator^=(EdgeAntialiasingMask& a, const EdgeAntialiasingMask b) noexcept
    {
        return a = static_cast<EdgeAntialiasingMask>(static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(a) ^ static_cast<std::underlying_type_t<EdgeAntialiasingMask>>(b));
    }

    class LayerContentsFilter: public ns::String
    {
    public:
        using String::String;
        using String::operator=;

        LayerContentsFilter() = delete;
        LayerContentsFilter(const char* name):
            ns::String{*static_cast<id*>(dlsym(RTLD_DEFAULT, name))}
        {
        }
    };

    inline const LayerContentsFilter FilterNearest{"kCAFilterNearest"};
    inline const LayerContentsFilter FilterLinear{"kCAFilterLinear"};
    inline const LayerContentsFilter FilterTrilinear{"kCAFilterTrilinear"};

    class Layer: public ns::Object
    {
    public:
        METALPP_PRIVATE_CLS("CALayer");

        METALPP_PRIVATE_SEL(anchorPoint, "anchorPoint");
        METALPP_PRIVATE_SEL(setAnchorPoint_, "setAnchorPoint:");
        METALPP_PRIVATE_SEL(frame, "frame");
        METALPP_PRIVATE_SEL(setFrame_, "setFrame:");
        METALPP_PRIVATE_SEL(masksToBounds, "masksToBounds");
        METALPP_PRIVATE_SEL(setMasksToBounds_, "setMasksToBounds:");
        METALPP_PRIVATE_SEL(minificationFilter, "minificationFilter");
        METALPP_PRIVATE_SEL(setMinificationFilter_, "setMinificationFilter:");
        METALPP_PRIVATE_SEL(magnificationFilter, "magnificationFilter");
        METALPP_PRIVATE_SEL(setMagnificationFilter_, "setMagnificationFilter:");
        METALPP_PRIVATE_SEL(autoresizingMask, "autoresizingMask");
        METALPP_PRIVATE_SEL(setAutoresizingMask_, "setAutoresizingMask:");
        METALPP_PRIVATE_SEL(backgroundColor, "backgroundColor");
        METALPP_PRIVATE_SEL(setBackgroundColor_, "setBackgroundColor:");
        METALPP_PRIVATE_SEL(edgeAntialiasingMask, "edgeAntialiasingMask");
        METALPP_PRIVATE_SEL(setEdgeAntialiasingMask_, "setEdgeAntialiasingMask:");

        using Object::Object;
        using Object::operator=;

        Layer() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto anchorPoint() const noexcept
        {
            return sendMessage<cg::Point>(METALPP_SEL(anchorPoint));
        }

        void setAnchorPoint(const cg::Point& anchorPoint) noexcept
        {
            sendMessage(METALPP_SEL(setAnchorPoint_), anchorPoint);
        }

        [[nodiscard]] auto frame() const noexcept
        {
            return sendMessage<cg::Rect>(METALPP_SEL(frame));
        }

        void setFrame(cg::Rect frame) noexcept
        {
            sendMessage(METALPP_SEL(setFrame_), frame);
        }

        [[nodiscard]] auto masksToBounds() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(masksToBounds)) == YES;
        }

        void setMasksToBounds(const BOOL masksToBounds) noexcept
        {
            sendMessage(METALPP_SEL(setMasksToBounds_), masksToBounds ? YES : NO);
        }

        [[nodiscard]] auto minificationFilter() const noexcept
        {
            return LayerContentsFilter{sendMessage<id>(METALPP_SEL(minificationFilter))};
        }

        void setMinificationFilter(const LayerContentsFilter& minificationFilter) noexcept
        {
            sendMessage(METALPP_SEL(setMinificationFilter_), minificationFilter.get());
        }

        [[nodiscard]] auto magnificationFilter() const noexcept
        {
            return LayerContentsFilter{sendMessage<id>(METALPP_SEL(magnificationFilter))};
        }

        void setMagnificationFilter(const LayerContentsFilter& magnificationFilter) noexcept
        {
            sendMessage(METALPP_SEL(setMagnificationFilter_), magnificationFilter.get());
        }

        [[nodiscard]] auto edgeAntialiasingMask() const noexcept
        {
            return sendMessage<EdgeAntialiasingMask>(METALPP_SEL(edgeAntialiasingMask));
        }

        void setEdgeAntialiasingMask(const EdgeAntialiasingMask edgeAntialiasingMask) noexcept
        {
            sendMessage(METALPP_SEL(setEdgeAntialiasingMask_), edgeAntialiasingMask);
        }

        [[nodiscard]] auto backgroundColor() const noexcept
        {
            return cg::Color{CGColorRetain(sendMessage<CGColorRef>(METALPP_SEL(backgroundColor)))};
        }

        void setBackgroundColor(const cg::Color& backgroundColor) noexcept
        {
            sendMessage(METALPP_SEL(setBackgroundColor_), backgroundColor.get());
        }

        [[nodiscard]] auto autoresizingMask() const noexcept
        {
            return sendMessage<AutoresizingMask>(METALPP_SEL(autoresizingMask));
        }

        void setAutoresizingMask(const AutoresizingMask autoresizingMask) noexcept
        {
            sendMessage(METALPP_SEL(setAutoresizingMask_), autoresizingMask);
        }
    };
}

#endif
