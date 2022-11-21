#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "Buffer.hpp"
#include "CommandEncoder.hpp"
#include "RenderPipeline.hpp"
#include "Selectors.hpp"
#include "StageInputOutputDescriptor.hpp"

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

    struct ScissorRect final
    {
        bool operator==(const ScissorRect& other) const noexcept
        {
            return other.x == x && other.y == y && other.width == width && other.height == height;
        }

        bool operator!=(const ScissorRect& other) const noexcept
        {
            return other.x != x || other.y != y || other.width != width || other.height != height;
        }

        NSUInteger x, y, width, height;
    };

    struct Viewport final
    {
        bool operator==(const Viewport& other) const noexcept
        {
            return other.originX == originX && other.originY == originY && other.width == width && other.height == height && other.znear == znear && other.zfar == zfar;
        }

        bool operator!=(const Viewport& other) const noexcept
        {
            return other.originX != originX || other.originY != originY || other.width != width || other.height != height || other.znear != znear || other.zfar != zfar;
        }

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
            sendMessage(sel::setRenderPipelineState_, static_cast<id>(pipelineState));
        }

        void setVertexBuffer(const Buffer& buffer, const NSUInteger offset, const NSUInteger index) noexcept
        {
            sendMessage(sel::setVertexBuffer_offset_atIndex_,
                        static_cast<id>(buffer),
                        offset,
                        index);
        }

        void drawPrimitives(const PrimitiveType primitiveType, const NSUInteger vertexStart, const NSUInteger vertexCount) noexcept
        {
            sendMessage(sel::drawPrimitives_vertexStart_vertexCount_,
                        primitiveType,
                        vertexStart,
                        vertexCount);
        }

        void drawIndexedPrimitives(const PrimitiveType primitiveType, const NSUInteger indexCount, const IndexType indexType, const Buffer& indexBuffer, const NSUInteger indexBufferOffset) noexcept
        {
            sendMessage(sel::drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_,
                        primitiveType,
                        indexCount,
                        indexType,
                        static_cast<id>(indexBuffer),
                        indexBufferOffset);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
