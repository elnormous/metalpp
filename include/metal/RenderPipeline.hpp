#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Library.hpp"
#include "PixelFormat.hpp"
#include "Selectors.hpp"
#include "VertexDescriptor.hpp"

namespace mtl
{
    class Device;

    enum class BlendFactor: NSUInteger
    {
        Zero = 0,
        One = 1,
        SourceColor = 2,
        OneMinusSourceColor = 3,
        SourceAlpha = 4,
        OneMinusSourceAlpha = 5,
        DestinationColor = 6,
        OneMinusDestinationColor = 7,
        DestinationAlpha = 8,
        OneMinusDestinationAlpha = 9,
        SourceAlphaSaturated = 10,
        BlendColor = 11,
        OneMinusBlendColor = 12,
        BlendAlpha = 13,
        OneMinusBlendAlpha = 14,
        Source1Color              API_AVAILABLE(macos(10.12), ios(10.11)) = 15,
        OneMinusSource1Color      API_AVAILABLE(macos(10.12), ios(10.11)) = 16,
        Source1Alpha              API_AVAILABLE(macos(10.12), ios(10.11)) = 17,
        OneMinusSource1Alpha      API_AVAILABLE(macos(10.12), ios(10.11)) = 18,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class BlendOperation: NSUInteger
    {
        Add = 0,
        Subtract = 1,
        ReverseSubtract = 2,
        Min = 3,
        Max = 4,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class ColorWriteMask: NSUInteger
    {
        None  = 0,
        Red   = 0x1 << 3,
        Green = 0x1 << 2,
        Blue  = 0x1 << 1,
        Alpha = 0x1 << 0,
        All   = 0xf
    } API_AVAILABLE(macos(10.11), ios(8.0));

    inline constexpr ColorWriteMask operator&(const ColorWriteMask a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) & static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    inline constexpr ColorWriteMask operator|(const ColorWriteMask a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) | static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    inline constexpr ColorWriteMask operator^(const ColorWriteMask a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) ^ static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    inline constexpr ColorWriteMask operator~(const ColorWriteMask a) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(~static_cast<std::underlying_type_t<ColorWriteMask>>(a));
    }
    inline constexpr ColorWriteMask& operator&=(ColorWriteMask& a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return a = static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) & static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    inline constexpr ColorWriteMask& operator|=(ColorWriteMask& a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return a = static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) | static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    inline constexpr ColorWriteMask& operator^=(ColorWriteMask& a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return a = static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) ^ static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }

    enum class PrimitiveTopologyClass: NSUInteger
    {
        Unspecified = 0,
        Point = 1,
        Line = 2,
        Triangle = 3,
    } API_AVAILABLE(macos(10.11), ios(12.0));

    enum class TessellationPartitionMode: NSUInteger
    {
        Pow2 = 0,
        Integer = 1,
        FractionalOdd = 2,
        FractionalEven = 3,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class TessellationFactorStepFunction: NSUInteger
    {
        Constant = 0,
        PerPatch = 1,
        PerInstance = 2,
        PerPatchAndPerInstance = 3,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class TessellationFactorFormat: NSUInteger
    {
        Half = 0,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class TessellationControlPointIndexType: NSUInteger
    {
        None = 0,
        UInt16 = 1,
        UInt32 = 2,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    class RenderPipelineColorAttachmentDescriptor final: public ns::Object
    {
    public:
        RenderPipelineColorAttachmentDescriptor() = delete;

        [[nodiscard]] PixelFormat pixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(sel::pixelFormat);
        }

        void setPixelFormat(PixelFormat pixelFormat) noexcept
        {
            sendMessage(sel::setPixelFormat_, pixelFormat);
        }

        [[nodiscard]] bool isBlendingEnabled() const noexcept
        {
            return sendMessage<BOOL>(sel::isBlendingEnabled) == YES;
        }

        void setBlendingEnabled(bool blendingEnabled) noexcept
        {
            sendMessage(sel::setBlendingEnabled_, blendingEnabled ? YES : NO);
        }

        [[nodiscard]] BlendFactor sourceRGBBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(sel::sourceRGBBlendFactor);
        }

        void setSourceRGBBlendFactor(BlendFactor sourceRGBBlendFactor) noexcept
        {
            sendMessage(sel::setSourceRGBBlendFactor_, sourceRGBBlendFactor);
        }

        [[nodiscard]] BlendFactor destinationRGBBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(sel::destinationRGBBlendFactor);
        }

        void setDestinationRGBBlendFactor(BlendFactor destinationRGBBlendFactor) noexcept
        {
            sendMessage(sel::setDestinationRGBBlendFactor_, destinationRGBBlendFactor);
        }

        [[nodiscard]] BlendOperation rgbBlendOperation() const noexcept
        {
            return sendMessage<BlendOperation>(sel::rgbBlendOperation);
        }

        void setRgbBlendOperation(BlendOperation rgbBlendOperation) noexcept
        {
            sendMessage(sel::setRgbBlendOperation_, rgbBlendOperation);
        }

        [[nodiscard]] BlendFactor sourceAlphaBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(sel::sourceAlphaBlendFactor);
        }

        void setSourceAlphaBlendFactor(BlendFactor sourceAlphaBlendFactor) noexcept
        {
            sendMessage(sel::setSourceAlphaBlendFactor_, sourceAlphaBlendFactor);
        }

        [[nodiscard]] BlendFactor destinationAlphaBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(sel::destinationAlphaBlendFactor);
        }

        void setDestinationAlphaBlendFactor(BlendFactor destinationAlphaBlendFactor) noexcept
        {
            sendMessage(sel::setDestinationAlphaBlendFactor_, destinationAlphaBlendFactor);
        }

        [[nodiscard]] BlendOperation alphaBlendOperation() const noexcept
        {
            return sendMessage<BlendOperation>(sel::alphaBlendOperation);
        }

        void setAlphaBlendOperation(BlendOperation alphaBlendOperation) noexcept
        {
            sendMessage(sel::setAlphaBlendOperation_, alphaBlendOperation);
        }

        [[nodiscard]] ColorWriteMask writeMask() const noexcept
        {
            return sendMessage<ColorWriteMask>(sel::writeMask);
        }

        void setWriteMask(ColorWriteMask writeMask) noexcept
        {
            sendMessage(sel::setWriteMask_, writeMask);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineColorAttachmentDescriptorArray final: public ns::Object
    {
    public:
        RenderPipelineColorAttachmentDescriptorArray() = delete;

        [[nodiscard]] RenderPipelineColorAttachmentDescriptor operator[](const NSUInteger index) const noexcept
        {
            return objectAtIndexedSubscript(index);
        }

        [[nodiscard]] RenderPipelineColorAttachmentDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            return getRetained<RenderPipelineColorAttachmentDescriptor>(ns::sel::objectAtIndexedSubscript_, index);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineDescriptor final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLRenderPipelineDescriptor");
    public:
        RenderPipelineDescriptor() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] ns::String label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] Function vertexFunction() const noexcept
        {
            return getRetained<Function>(sel::vertexFunction);
        }

        void setVertexFunction(const Function& function) noexcept
        {
            sendMessage(sel::setVertexFunction_, static_cast<id>(function));
        }

        [[nodiscard]] Function fragmentFunction() const noexcept
        {
            return getRetained<Function>(sel::fragmentFunction);
        }

        void setFragmentFunction(const Function& function) noexcept
        {
            sendMessage(sel::setFragmentFunction_, static_cast<id>(function));
        }

        [[nodiscard]] VertexDescriptor vertexDescriptor() const noexcept
        {
            return getRetained<VertexDescriptor>(sel::vertexDescriptor);
        }

        void setVertexDescriptor(const VertexDescriptor& vertexDescriptor) noexcept
        {
            sendMessage(sel::setVertexDescriptor_, static_cast<id>(vertexDescriptor));
        }

        [[nodiscard]] RenderPipelineColorAttachmentDescriptorArray colorAttachments() const noexcept
        {
            return getRetained<RenderPipelineColorAttachmentDescriptorArray>(sel::colorAttachments);
        }

        [[nodiscard]] PixelFormat depthAttachmentPixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(sel::depthAttachmentPixelFormat);
        }

        void setDepthAttachmentPixelFormat(const PixelFormat pixelFormat) noexcept
        {
            sendMessage(sel::setDepthAttachmentPixelFormat_, pixelFormat);
        }

        [[nodiscard]] PixelFormat stencilAttachmentPixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(sel::stencilAttachmentPixelFormat);
        }

        void setStencilAttachmentPixelFormat(const PixelFormat pixelFormat) noexcept
        {
            sendMessage(sel::setStencilAttachmentPixelFormat_, pixelFormat);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState() = delete;

        [[nodiscard]] Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            return getRetained<ns::String>(sel::label);
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(sel::setLabel_, static_cast<id>(label));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
