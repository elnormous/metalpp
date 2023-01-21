#ifndef METALPP_APPKIT_VIEW_HPP
#define METALPP_APPKIT_VIEW_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/Geometry.hpp"
#include "../quartzcore/Layer.hpp"
#include "Graphics.hpp"

namespace ns
{
    class Window;

    enum class AutoresizingMaskOptions: UInteger
    {
        NotSizable            =  0,
        MinXMargin            =  1,
        WidthSizable            =  2,
        MaxXMargin            =  4,
        MinYMargin            =  8,
        HeightSizable            = 16,
        MaxYMargin            = 32
    };

    [[nodiscard]] inline constexpr AutoresizingMaskOptions operator&(const AutoresizingMaskOptions a, const AutoresizingMaskOptions b) noexcept
    {
        return static_cast<AutoresizingMaskOptions>(static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a) & static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(b));
    }
    [[nodiscard]] inline constexpr AutoresizingMaskOptions operator|(const AutoresizingMaskOptions a, const AutoresizingMaskOptions b) noexcept
    {
        return static_cast<AutoresizingMaskOptions>(static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a) | static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(b));
    }
    [[nodiscard]] inline constexpr AutoresizingMaskOptions operator^(const AutoresizingMaskOptions a, const AutoresizingMaskOptions b) noexcept
    {
        return static_cast<AutoresizingMaskOptions>(static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a) ^ static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(b));
    }
    [[nodiscard]] inline constexpr AutoresizingMaskOptions operator~(const AutoresizingMaskOptions a) noexcept
    {
        return static_cast<AutoresizingMaskOptions>(~static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a));
    }
    inline constexpr AutoresizingMaskOptions& operator&=(AutoresizingMaskOptions& a, const AutoresizingMaskOptions b) noexcept
    {
        return a = static_cast<AutoresizingMaskOptions>(static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a) & static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(b));
    }
    inline constexpr AutoresizingMaskOptions& operator|=(AutoresizingMaskOptions& a, const AutoresizingMaskOptions b) noexcept
    {
        return a = static_cast<AutoresizingMaskOptions>(static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a) | static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(b));
    }
    inline constexpr AutoresizingMaskOptions& operator^=(AutoresizingMaskOptions& a, const AutoresizingMaskOptions b) noexcept
    {
        return a = static_cast<AutoresizingMaskOptions>(static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(a) ^ static_cast<std::underlying_type_t<AutoresizingMaskOptions>>(b));
    }

    class View: public Object
    {
    public:
        METALPP_PRIVATE_CLS("NSView");

        METALPP_PRIVATE_SEL(initWithFrame_, "initWithFrame:");
        METALPP_PRIVATE_SEL(autoresizingMask, "autoresizingMask");
        METALPP_PRIVATE_SEL(window, "window");
        METALPP_PRIVATE_SEL(superview, "superview");
        METALPP_PRIVATE_SEL(addSubview_, "addSubview:");
        METALPP_PRIVATE_SEL(addSubview_positioned_relativeTo_, "addSubview:positioned:relativeTo:");
        METALPP_PRIVATE_SEL(removeFromSuperview, "removeFromSuperview");
        METALPP_PRIVATE_SEL(setAutoresizingMask_, "setAutoresizingMask:");
        METALPP_PRIVATE_SEL(frame, "frame");
        METALPP_PRIVATE_SEL(setFrame_, "setFrame:");
        METALPP_PRIVATE_SEL(convertPoint_fromView_, "convertPoint:fromView:");
        METALPP_PRIVATE_SEL(convertPoint_toView_, "convertPoint:toView:");
        METALPP_PRIVATE_SEL(convertSize_fromView_, "convertSize:fromView:");
        METALPP_PRIVATE_SEL(convertSize_toView_, "convertSize:toView:");
        METALPP_PRIVATE_SEL(convertRect_fromView_, "convertRect:fromView:");
        METALPP_PRIVATE_SEL(convertRect_toView_, "convertRect:toView:");
        METALPP_PRIVATE_SEL(wantsLayer, "wantsLayer");
        METALPP_PRIVATE_SEL(setWantsLayer_, "setWantsLayer:");
        METALPP_PRIVATE_SEL(layer, "layer");
        METALPP_PRIVATE_SEL(setLayer_, "setLayer:");

        using Object::Object;
        using Object::operator=;

        View() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), adopt}
        {
        }

        View(const Rect& frameRect) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(initWithFrame_), frameRect), adopt}
        {
        }

        [[nodiscard]] Window window() const noexcept;

        [[nodiscard]] auto superview() const noexcept
        {
            const id view = sendMessage<id>(METALPP_SEL(superview));
            return View{view};
        }

        void addSubview(const View& view) noexcept
        {
            sendMessage(METALPP_SEL(addSubview_), view.get());
        }

        void addSubview(const View& view, const WindowOrderingMode place, View otherView = nullptr) noexcept
        {
            sendMessage(METALPP_SEL(addSubview_positioned_relativeTo_), view.get(), place, otherView.get());
        }

        void removeFromSuperview() noexcept
        {
            sendMessage(METALPP_SEL(removeFromSuperview));
        }

        [[nodiscard]] auto autoresizingMask() const noexcept
        {
            return sendMessage<AutoresizingMaskOptions>(METALPP_SEL(autoresizingMask));
        }

        void setAutoresizingMask(const AutoresizingMaskOptions autoresizingMask) noexcept
        {
            sendMessage(METALPP_SEL(setAutoresizingMask_), autoresizingMask);
        }

        [[nodiscard]] auto frame() const noexcept
        {
            return sendMessage<Rect>(METALPP_SEL(frame));
        }

        void setFrame(const Rect& frame) noexcept
        {
            sendMessage(METALPP_SEL(setFrame_), frame);
        }
        
        [[nodiscard]] auto convertFromView(const Point& point, const View& view) const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(convertPoint_fromView_), point, view.get());
        }

        [[nodiscard]] auto convertToView(const Point& point, const View& view) const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(convertPoint_toView_), point, view.get());
        }

        [[nodiscard]] auto convertFromView(const Size& size, const View& view) const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(convertSize_fromView_), size, view.get());
        }

        [[nodiscard]] auto convertToView(const Size& size, const View& view) const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(convertSize_toView_), size, view.get());
        }

        [[nodiscard]] auto convertFromView(const Rect& rect, const View& view) const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(convertRect_fromView_), rect, view.get());
        }

        [[nodiscard]] auto convertToView(const Rect& rect, const View& view) const noexcept
        {
            return sendMessage<Point>(METALPP_SEL(convertRect_toView_), rect, view.get());
        }

        [[nodiscard]] auto wantsLayer() const noexcept API_AVAILABLE(macos(10.5))
        {
            return sendMessage<BOOL>(METALPP_SEL(wantsLayer)) == YES;
        }

        void setWantsLayer(const bool wantsLayer) noexcept API_AVAILABLE(macos(10.5))
        {
            sendMessage(METALPP_SEL(setWantsLayer_), wantsLayer ? YES : NO);
        }

        [[nodiscard]] auto layer() const noexcept API_AVAILABLE(macos(10.5))
        {
            return ca::Layer{sendMessage<id>(METALPP_SEL(layer))};
        }

        void setLayer(const ca::Layer& layer) noexcept API_AVAILABLE(macos(10.5))
        {
            sendMessage(METALPP_SEL(setLayer_), layer.get());
        }
    };
}

#endif
