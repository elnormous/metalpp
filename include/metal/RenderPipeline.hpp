#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Object.hpp"
#include "Library.hpp"
#include "PixelFormat.hpp"
#include "VertexDescriptor.hpp"

namespace mtl
{
    class Device;

    enum class BlendFactor: ns::UInteger
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

    enum class BlendOperation: ns::UInteger
    {
        Add = 0,
        Subtract = 1,
        ReverseSubtract = 2,
        Min = 3,
        Max = 4,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class ColorWriteMask: ns::UInteger
    {
        None  = 0,
        Red   = 0x1 << 3,
        Green = 0x1 << 2,
        Blue  = 0x1 << 1,
        Alpha = 0x1 << 0,
        All   = 0xf
    } API_AVAILABLE(macos(10.11), ios(8.0));

    [[nodiscard]] inline constexpr ColorWriteMask operator&(const ColorWriteMask a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) & static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    [[nodiscard]] inline constexpr ColorWriteMask operator|(const ColorWriteMask a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) | static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    [[nodiscard]] inline constexpr ColorWriteMask operator^(const ColorWriteMask a, const ColorWriteMask b) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
    {
        return static_cast<ColorWriteMask>(static_cast<std::underlying_type_t<ColorWriteMask>>(a) ^ static_cast<std::underlying_type_t<ColorWriteMask>>(b));
    }
    [[nodiscard]] inline constexpr ColorWriteMask operator~(const ColorWriteMask a) noexcept API_AVAILABLE(macos(10.11), ios(8.0))
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

    enum class PrimitiveTopologyClass: ns::UInteger
    {
        Unspecified = 0,
        Point = 1,
        Line = 2,
        Triangle = 3,
    } API_AVAILABLE(macos(10.11), ios(12.0));

    enum class TessellationPartitionMode: ns::UInteger
    {
        Pow2 = 0,
        Integer = 1,
        FractionalOdd = 2,
        FractionalEven = 3,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class TessellationFactorStepFunction: ns::UInteger
    {
        Constant = 0,
        PerPatch = 1,
        PerInstance = 2,
        PerPatchAndPerInstance = 3,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class TessellationFactorFormat: ns::UInteger
    {
        Half = 0,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class TessellationControlPointIndexType: ns::UInteger
    {
        None = 0,
        UInt16 = 1,
        UInt32 = 2,
    } API_AVAILABLE(macos(10.12), ios(10.0));

    class RenderPipelineColorAttachmentDescriptor final: public ns::Object, public ns::Copying
    {
    public:
        METALPP_PRIVATE_CLS("MTLRenderPipelineColorAttachmentDescriptor");

        METALPP_PRIVATE_SEL(pixelFormat, "pixelFormat");
        METALPP_PRIVATE_SEL(setPixelFormat_, "setPixelFormat:");
        METALPP_PRIVATE_SEL(isBlendingEnabled, "isBlendingEnabled");
        METALPP_PRIVATE_SEL(setBlendingEnabled_, "setBlendingEnabled:");
        METALPP_PRIVATE_SEL(sourceRGBBlendFactor, "sourceRGBBlendFactor");
        METALPP_PRIVATE_SEL(setSourceRGBBlendFactor_, "setSourceRGBBlendFactor:");
        METALPP_PRIVATE_SEL(destinationRGBBlendFactor, "destinationRGBBlendFactor");
        METALPP_PRIVATE_SEL(setDestinationRGBBlendFactor_, "setDestinationRGBBlendFactor:");
        METALPP_PRIVATE_SEL(rgbBlendOperation, "rgbBlendOperation");
        METALPP_PRIVATE_SEL(setRgbBlendOperation_, "setRgbBlendOperation:");
        METALPP_PRIVATE_SEL(sourceAlphaBlendFactor, "sourceAlphaBlendFactor");
        METALPP_PRIVATE_SEL(setSourceAlphaBlendFactor_, "setSourceAlphaBlendFactor:");
        METALPP_PRIVATE_SEL(destinationAlphaBlendFactor, "destinationAlphaBlendFactor");
        METALPP_PRIVATE_SEL(setDestinationAlphaBlendFactor_, "setDestinationAlphaBlendFactor:");
        METALPP_PRIVATE_SEL(alphaBlendOperation, "alphaBlendOperation");
        METALPP_PRIVATE_SEL(setAlphaBlendOperation_, "setAlphaBlendOperation:");
        METALPP_PRIVATE_SEL(writeMask, "writeMask");
        METALPP_PRIVATE_SEL(setWriteMask_, "setWriteMask:");

        using Object::Object;
        using Object::operator=;

        RenderPipelineColorAttachmentDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto pixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(METALPP_SEL(pixelFormat));
        }

        void setPixelFormat(PixelFormat pixelFormat) noexcept
        {
            sendMessage(METALPP_SEL(setPixelFormat_), pixelFormat);
        }

        [[nodiscard]] auto isBlendingEnabled() const noexcept
        {
            return sendMessage<BOOL>(METALPP_SEL(isBlendingEnabled)) == YES;
        }

        void setBlendingEnabled(bool blendingEnabled) noexcept
        {
            sendMessage(METALPP_SEL(setBlendingEnabled_), blendingEnabled ? YES : NO);
        }

        [[nodiscard]] auto sourceRGBBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(METALPP_SEL(sourceRGBBlendFactor));
        }

        void setSourceRGBBlendFactor(BlendFactor sourceRGBBlendFactor) noexcept
        {
            sendMessage(METALPP_SEL(setSourceRGBBlendFactor_), sourceRGBBlendFactor);
        }

        [[nodiscard]] auto destinationRGBBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(METALPP_SEL(destinationRGBBlendFactor));
        }

        void setDestinationRGBBlendFactor(BlendFactor destinationRGBBlendFactor) noexcept
        {
            sendMessage(METALPP_SEL(setDestinationRGBBlendFactor_), destinationRGBBlendFactor);
        }

        [[nodiscard]] auto rgbBlendOperation() const noexcept
        {
            return sendMessage<BlendOperation>(METALPP_SEL(rgbBlendOperation));
        }

        void setRgbBlendOperation(BlendOperation rgbBlendOperation) noexcept
        {
            sendMessage(METALPP_SEL(setRgbBlendOperation_), rgbBlendOperation);
        }

        [[nodiscard]] auto sourceAlphaBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(METALPP_SEL(sourceAlphaBlendFactor));
        }

        void setSourceAlphaBlendFactor(BlendFactor sourceAlphaBlendFactor) noexcept
        {
            sendMessage(METALPP_SEL(setSourceAlphaBlendFactor_), sourceAlphaBlendFactor);
        }

        [[nodiscard]] auto destinationAlphaBlendFactor() const noexcept
        {
            return sendMessage<BlendFactor>(METALPP_SEL(destinationAlphaBlendFactor));
        }

        void setDestinationAlphaBlendFactor(BlendFactor destinationAlphaBlendFactor) noexcept
        {
            sendMessage(METALPP_SEL(setDestinationAlphaBlendFactor_), destinationAlphaBlendFactor);
        }

        [[nodiscard]] auto alphaBlendOperation() const noexcept
        {
            return sendMessage<BlendOperation>(METALPP_SEL(alphaBlendOperation));
        }

        void setAlphaBlendOperation(BlendOperation alphaBlendOperation) noexcept
        {
            sendMessage(METALPP_SEL(setAlphaBlendOperation_), alphaBlendOperation);
        }

        [[nodiscard]] auto writeMask() const noexcept
        {
            return sendMessage<ColorWriteMask>(METALPP_SEL(writeMask));
        }

        void setWriteMask(ColorWriteMask writeMask) noexcept
        {
            sendMessage(METALPP_SEL(setWriteMask_), writeMask);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineColorAttachmentDescriptorArray final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(objectAtIndexedSubscript_, "objectAtIndexedSubscript:");
        METALPP_PRIVATE_SEL(setObject_atIndexedSubscript_, "setObject:atIndexedSubscript:");

        using Object::Object;
        using Object::operator=;

        RenderPipelineColorAttachmentDescriptorArray() = delete;

        [[nodiscard]] auto object(const ns::UInteger index) const noexcept
        {
            return RenderPipelineColorAttachmentDescriptor{sendMessage<id>(METALPP_SEL(objectAtIndexedSubscript_), index)};
        }

        void setObject(const RenderPipelineColorAttachmentDescriptor& derscriptor) noexcept
        {
            sendMessage(METALPP_SEL(setObject_atIndexedSubscript_), derscriptor, index);
        }

        [[nodiscard]] auto operator[](const ns::UInteger index) const noexcept
        {
            return object(index);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineDescriptor final: public ns::Object, public ns::Copying
    {
    public:
        METALPP_PRIVATE_CLS("MTLRenderPipelineDescriptor");

        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(setLabel_, "setLabel:");
        METALPP_PRIVATE_SEL(vertexFunction, "vertexFunction");
        METALPP_PRIVATE_SEL(setVertexFunction_, "setVertexFunction:");
        METALPP_PRIVATE_SEL(fragmentFunction, "fragmentFunction");
        METALPP_PRIVATE_SEL(setFragmentFunction_, "setFragmentFunction:");
        METALPP_PRIVATE_SEL(vertexDescriptor, "vertexDescriptor");
        METALPP_PRIVATE_SEL(setVertexDescriptor_, "setVertexDescriptor:");
        METALPP_PRIVATE_SEL(sampleCount, "sampleCount");
        METALPP_PRIVATE_SEL(setSampleCount_, "setSampleCount:");
        METALPP_PRIVATE_SEL(colorAttachments, "colorAttachments");
        METALPP_PRIVATE_SEL(depthAttachmentPixelFormat, "depthAttachmentPixelFormat");
        METALPP_PRIVATE_SEL(setDepthAttachmentPixelFormat_, "setDepthAttachmentPixelFormat:");
        METALPP_PRIVATE_SEL(stencilAttachmentPixelFormat, "stencilAttachmentPixelFormat");
        METALPP_PRIVATE_SEL(setStencilAttachmentPixelFormat_, "setStencilAttachmentPixelFormat:");

        RenderPipelineDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        void setLabel(const ns::String& label) noexcept
        {
            sendMessage(METALPP_SEL(setLabel_), label.get());
        }

        [[nodiscard]] auto vertexFunction() const noexcept
        {
            return Function{sendMessage<id>(METALPP_SEL(vertexFunction))};
        }

        void setVertexFunction(const Function& function) noexcept
        {
            sendMessage(METALPP_SEL(setVertexFunction_), function.get());
        }

        [[nodiscard]] auto fragmentFunction() const noexcept
        {
            return Function{sendMessage<id>(METALPP_SEL(fragmentFunction))};
        }

        void setFragmentFunction(const Function& function) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentFunction_), function.get());
        }

        [[nodiscard]] auto vertexDescriptor() const noexcept
        {
            return VertexDescriptor{sendMessage<id>(METALPP_SEL(vertexDescriptor))};
        }

        void setVertexDescriptor(const VertexDescriptor& vertexDescriptor) noexcept
        {
            sendMessage(METALPP_SEL(setVertexDescriptor_), vertexDescriptor.get());
        }

        [[nodiscard]] auto sampleCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(sampleCount));
        }

        void setSampleCount(const ns::UInteger sampleCount) noexcept
        {
            sendMessage(METALPP_SEL(setSampleCount_), sampleCount);
        }

        [[nodiscard]] auto colorAttachments() const noexcept
        {
            return RenderPipelineColorAttachmentDescriptorArray{sendMessage<id>(METALPP_SEL(colorAttachments))};
        }

        [[nodiscard]] auto depthAttachmentPixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(METALPP_SEL(depthAttachmentPixelFormat));
        }

        void setDepthAttachmentPixelFormat(const PixelFormat pixelFormat) noexcept
        {
            sendMessage(METALPP_SEL(setDepthAttachmentPixelFormat_), pixelFormat);
        }

        [[nodiscard]] auto stencilAttachmentPixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(METALPP_SEL(stencilAttachmentPixelFormat));
        }

        void setStencilAttachmentPixelFormat(const PixelFormat pixelFormat) noexcept
        {
            sendMessage(METALPP_SEL(setStencilAttachmentPixelFormat_), pixelFormat);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineState final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(label, "label");
        METALPP_PRIVATE_SEL(device, "device");

        using Object::Object;
        using Object::operator=;

        RenderPipelineState() = delete;

        [[nodiscard]] auto label() const noexcept
        {
            return ns::String{sendMessage<id>(METALPP_SEL(label))};
        }

        [[nodiscard]] Device device() const noexcept;
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
