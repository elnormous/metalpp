#ifndef METALPP_QUARTZCORE_LAYER_HPP
#define METALPP_QUARTZCORE_LAYER_HPP

#include <dlfcn.h>
#include "../objc/Object.hpp"
#include "../corefoundation/Types.hpp"
#include "../foundation/String.hpp"
#include "Selectors.hpp"

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

    inline constexpr AutoresizingMask operator&(const AutoresizingMask a, const AutoresizingMask b) noexcept
    {
        return static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) & static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    inline constexpr AutoresizingMask operator|(const AutoresizingMask a, const AutoresizingMask b) noexcept
    {
        return static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) | static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    inline constexpr AutoresizingMask operator^(const AutoresizingMask a, const AutoresizingMask b) noexcept
    {
        return static_cast<AutoresizingMask>(static_cast<std::underlying_type_t<AutoresizingMask>>(a) ^ static_cast<std::underlying_type_t<AutoresizingMask>>(b));
    }
    inline constexpr AutoresizingMask operator~(const AutoresizingMask a) noexcept
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
        LayerContentsFilter() = delete;
    };

    inline const LayerContentsFilter filterNearest{objc::sendMessage<id>(*static_cast<id*>(dlsym(RTLD_DEFAULT, "kCAFilterNearest")), ns::sel::retain)};
    inline const LayerContentsFilter filterLinear{objc::sendMessage<id>(*static_cast<id*>(dlsym(RTLD_DEFAULT, "kCAFilterLinear")), ns::sel::retain)};
    inline const LayerContentsFilter filterTrilinear{objc::sendMessage<id>(*static_cast<id*>(dlsym(RTLD_DEFAULT, "kCAFilterTrilinear")), ns::sel::retain)};

    class Layer: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("CALayer");
    public:
        using Object::Object;

        Layer() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] auto anchorPoint() const noexcept
        {
            return sendMessage<cg::Point>(sel::anchorPoint);
        }

        void setAnchorPoint(const cg::Point& anchorPoint) noexcept
        {
            sendMessage(sel::setAnchorPoint_, anchorPoint);
        }

        [[nodiscard]] auto frame() const noexcept
        {
            return sendMessage<cg::Rect>(sel::frame);
        }

        void setFrame(cg::Rect frame) noexcept
        {
            sendMessage(sel::setFrame_, frame);
        }

        [[nodiscard]] auto masksToBounds() const noexcept
        {
            return sendMessage<BOOL>(sel::masksToBounds) == YES;
        }

        void setMasksToBounds(const BOOL masksToBounds) noexcept
        {
            sendMessage(sel::setMasksToBounds_, masksToBounds ? YES : NO);
        }

        [[nodiscard]] auto minificationFilter() const noexcept
        {
            return getRetained<LayerContentsFilter>(sel::minificationFilter);
        }

        void setMinificationFilter(const LayerContentsFilter& minificationFilter) noexcept
        {
            sendMessage(sel::setMinificationFilter_, static_cast<id>(minificationFilter));
        }

        [[nodiscard]] auto magnificationFilter() const noexcept
        {
            return getRetained<LayerContentsFilter>(sel::magnificationFilter);
        }

        void setMagnificationFilter(const LayerContentsFilter& magnificationFilter) noexcept
        {
            sendMessage(sel::setMagnificationFilter_, static_cast<id>(magnificationFilter));
        }

        [[nodiscard]] auto edgeAntialiasingMask() const noexcept
        {
            return sendMessage<EdgeAntialiasingMask>(sel::edgeAntialiasingMask);
        }

        void setEdgeAntialiasingMask(const EdgeAntialiasingMask edgeAntialiasingMask) noexcept
        {
            sendMessage(sel::setEdgeAntialiasingMask_, edgeAntialiasingMask);
        }

        [[nodiscard]] auto autoresizingMask() const noexcept
        {
            return sendMessage<AutoresizingMask>(sel::autoresizingMask);
        }

        void setAutoresizingMask(const AutoresizingMask autoresizingMask) noexcept
        {
            sendMessage(sel::setAutoresizingMask_, autoresizingMask);
        }
    };
}

#endif
