#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"
#include "Buffer.hpp"
#include "CommandEncoder.hpp"
#include "RenderPipeline.hpp"
#include "Sampler.hpp"
#include "Selectors.hpp"
#include "StageInputOutputDescriptor.hpp"
#include "Texture.hpp"

namespace mtl
{
    enum class PrimitiveType: ns::UInteger
    {
        Point = 0,
        Line = 1,
        LineStrip = 2,
        Triangle = 3,
        TriangleStrip = 4,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class VisibilityResultMode: ns::UInteger
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

        ns::UInteger x, y, width, height;
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

    enum class CullMode: ns::UInteger
    {
        None = 0,
        Front = 1,
        Back = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class Winding: ns::UInteger
    {
        Clockwise = 0,
        CounterClockwise = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class DepthClipMode: ns::UInteger
    {
        Clip = 0,
        Clamp = 1,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class TriangleFillMode: ns::UInteger
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
            sendMessage(sel::setRenderPipelineState_, pipelineState.get());
        }

        void setVertexBuffer(const Buffer& buffer, const ns::UInteger offset, const ns::UInteger index) noexcept
        {
            sendMessage(sel::setVertexBuffer_offset_atIndex_,
                        buffer.get(),
                        offset,
                        index);
        }

        void setFragmentBuffer(const Buffer& buffer, const ns::UInteger offset, ns::UInteger index)  noexcept
        {
            sendMessage(sel::setFragmentBuffer_offset_atIndex_,
                        buffer.get(),
                        offset,
                        index);
        }

        void setFragmentTexture(const Texture& texture, ns::UInteger index)  noexcept
        {
            sendMessage(sel::setFragmentTexture_atIndex_,
                        texture.get(),
                        index);
        }

        void setFragmentSamplerState(const SamplerState& sampler, ns::UInteger index)  noexcept
        {
            sendMessage(sel::setFragmentSamplerState_atIndex_,
                        sampler.get(),
                        index);
        }

        void drawPrimitives(const PrimitiveType primitiveType, const ns::UInteger vertexStart, const ns::UInteger vertexCount) noexcept
        {
            sendMessage(sel::drawPrimitives_vertexStart_vertexCount_,
                        primitiveType,
                        vertexStart,
                        vertexCount);
        }

        void drawIndexedPrimitives(const PrimitiveType primitiveType, const ns::UInteger indexCount, const IndexType indexType, const Buffer& indexBuffer, const ns::UInteger indexBufferOffset) noexcept
        {
            sendMessage(sel::drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_,
                        primitiveType,
                        indexCount,
                        indexType,
                        indexBuffer.get(),
                        indexBufferOffset);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
