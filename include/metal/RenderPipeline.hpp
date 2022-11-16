#ifndef METALPP_METAL_RENDERPIPELINE_HPP
#define METALPP_METAL_RENDERPIPELINE_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Classes.hpp"
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

    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineColorAttachmentDescriptorArray final: public ns::Object
    {
    public:
        RenderPipelineColorAttachmentDescriptorArray() = delete;

        [[nodiscard]] RenderPipelineColorAttachmentDescriptor operator[](const std::size_t index) const noexcept
        {
            return objectAtIndexedSubscript(static_cast<NSUInteger>(index));
        }

        [[nodiscard]] RenderPipelineColorAttachmentDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndexedSubscript_,
                                                    index);
            return RenderPipelineColorAttachmentDescriptor{objc::sendMessage<id>(object, ns::sel::retain)};
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineDescriptor final: public ns::Object
    {
    public:
        RenderPipelineDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(mtl::cls::renderPipelineDescriptor, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String& label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }

        [[nodiscard]] mtl::Function vertexFunction() const noexcept
        {
            const id function = objc::sendMessage<id>(*this, sel::vertexFunction);
            return mtl::Function{objc::sendMessage<id>(function, ns::sel::retain)};
        }

        void setVertexFunction(const mtl::Function& function) noexcept
        {
            objc::sendMessage(*this, sel::setVertexFunction_, static_cast<id>(function));
        }

        [[nodiscard]] mtl::Function fragmentFunction() const noexcept
        {
            const id function = objc::sendMessage<id>(*this, sel::fragmentFunction);
            return mtl::Function{objc::sendMessage<id>(function, ns::sel::retain)};
        }

        void setFragmentFunction(const mtl::Function& function) noexcept
        {
            objc::sendMessage(*this, sel::setFragmentFunction_, static_cast<id>(function));
        }

        [[nodiscard]] mtl::VertexDescriptor vertexDescriptor() const noexcept
        {
            const id vertexDescriptor = objc::sendMessage<id>(*this, sel::vertexDescriptor);
            return mtl::VertexDescriptor{objc::sendMessage<id>(vertexDescriptor, ns::sel::retain)};
        }

        void setVertexDescriptor(const mtl::VertexDescriptor& vertexDescriptor) noexcept
        {
            objc::sendMessage(*this, sel::setVertexDescriptor_, static_cast<id>(vertexDescriptor));
        }

        [[nodiscard]] mtl::RenderPipelineColorAttachmentDescriptorArray colorAttachments() const noexcept
        {
            const id colorAttachments = objc::sendMessage<id>(*this, sel::colorAttachments);
            return mtl::RenderPipelineColorAttachmentDescriptorArray{objc::sendMessage<id>(colorAttachments, ns::sel::retain)};
        }

        [[nodiscard]] mtl::PixelFormat depthAttachmentPixelFormat() const noexcept
        {
            return objc::sendMessage<mtl::PixelFormat>(*this, sel::depthAttachmentPixelFormat);
        }

        void setDepthAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, sel::setDepthAttachmentPixelFormat_, pixelFormat);
        }

        [[nodiscard]] mtl::PixelFormat stencilAttachmentPixelFormat() const noexcept
        {
            return objc::sendMessage<mtl::PixelFormat>(*this, sel::stencilAttachmentPixelFormat);
        }

        void setStencilAttachmentPixelFormat(const mtl::PixelFormat pixelFormat) noexcept
        {
            objc::sendMessage(*this, sel::setStencilAttachmentPixelFormat_, pixelFormat);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderPipelineState final: public ns::Object
    {
    public:
        RenderPipelineState(const id p) noexcept: Object{p} {}

        Device device() const noexcept;

        [[nodiscard]] ns::String label() const noexcept
        {
            const id label = objc::sendMessage<id>(*this, sel::label);
            return ns::String{objc::sendMessage<id>(label, ns::sel::retain)};
        }

        void setLabel(const ns::String& label) noexcept
        {
            objc::sendMessage(*this, sel::setLabel_, static_cast<id>(label));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
