#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "CommandEncoder.hpp"
#include "RenderPipeline.hpp"
#include "Selectors.hpp"

namespace mtl
{
    enum class PrimitiveType: NSUInteger
    {
        Point = 0,
        Line = 1,
        LineStrip = 2,
        Triangle = 3,
        TriangleStrip = 4,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class VisibilityResultMode: NSUInteger
    {
        Disabled = 0,
        Boolean = 1,
        Counting API_AVAILABLE(macos(10.11), ios(9.0)) = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    struct ScissorRect
    {
        NSUInteger x, y, width, height;
    };

    struct Viewport
    {
        double originX, originY, width, height, znear, zfar;
    };

    enum class CullMode: NSUInteger
    {
        None = 0,
        Front = 1,
        Back = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class Winding: NSUInteger
    {
        Clockwise = 0,
        CounterClockwise = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class DepthClipMode: NSUInteger
    {
        Clip = 0,
        Clamp = 1,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class TriangleFillMode: NSUInteger
    {
        Fill = 0,
        Lines = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class RenderCommandEncoder final: public CommandEncoder
    {
    public:
        RenderCommandEncoder() = delete;

        void setRenderPipelineState(const RenderPipelineState& pipelineState) noexcept
        {
            objc::sendMessage(*this, sel::setRenderPipelineState_, static_cast<id>(pipelineState));
        }

        void setVertexBuffer(const Buffer& buffer, const NSUInteger offset, const NSUInteger index) noexcept
        {
            objc::sendMessage(*this, sel::setVertexBuffer_offset_atIndex_, static_cast<id>(buffer), offset, index);
        }

        void drawPrimitives(const PrimitiveType primitiveType, const NSUInteger vertexStart, const NSUInteger vertexCount) noexcept
        {
            objc::sendMessage(*this, sel::drawPrimitives_vertexStart_vertexCount_, primitiveType, vertexStart, vertexCount);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
