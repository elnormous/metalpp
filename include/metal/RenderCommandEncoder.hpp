#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <os/availability.h>
#include <array>
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "../foundation/Range.hpp"
#include "Buffer.hpp"
#include "CommandEncoder.hpp"
#include "DepthStencil.hpp"
#include "Fence.hpp"
#include "RenderPipeline.hpp"
#include "Sampler.hpp"
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
        [[nodiscard]] bool operator==(const ScissorRect& other) const noexcept
        {
            return other.x == x && other.y == y && other.width == width && other.height == height;
        }

        [[nodiscard]] bool operator!=(const ScissorRect& other) const noexcept
        {
            return other.x != x || other.y != y || other.width != width || other.height != height;
        }

        ns::UInteger x = 0;
        ns::UInteger y = 0;
        ns::UInteger width = 0;
        ns::UInteger height = 0;
    };

    struct Viewport final
    {
        [[nodiscard]] bool operator==(const Viewport& other) const noexcept
        {
            return other.originX == originX && other.originY == originY && other.width == width && other.height == height && other.znear == znear && other.zfar == zfar;
        }

        [[nodiscard]] bool operator!=(const Viewport& other) const noexcept
        {
            return other.originX != originX || other.originY != originY || other.width != width || other.height != height || other.znear != znear || other.zfar != zfar;
        }

        double originX = 0.0;
        double originY = 0.0;
        double width = 0.0;
        double height = 0.0;
        double znear = 0.0;
        double zfar = 0.0;
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

    enum class RenderStages: ns::UInteger
    {
        Vertex   = (1UL << 0),
        Fragment = (1UL << 1),
        Tile API_AVAILABLE(macos(12.0), ios(15.0)) = (1UL << 2),
        Object API_AVAILABLE(macos(13.0), ios(16.0))  = (1UL << 3),
        Mesh API_AVAILABLE(macos(13.0), ios(16.0))  = (1UL << 4),
    } API_AVAILABLE(macos(10.13), ios(10.0));

    [[nodiscard]] inline constexpr RenderStages operator&(const RenderStages a, const RenderStages b) noexcept
    {
        return static_cast<RenderStages>(static_cast<std::underlying_type_t<RenderStages>>(a) & static_cast<std::underlying_type_t<RenderStages>>(b));
    }
    [[nodiscard]] inline constexpr RenderStages operator|(const RenderStages a, const RenderStages b) noexcept
    {
        return static_cast<RenderStages>(static_cast<std::underlying_type_t<RenderStages>>(a) | static_cast<std::underlying_type_t<RenderStages>>(b));
    }
    [[nodiscard]] inline constexpr RenderStages operator^(const RenderStages a, const RenderStages b) noexcept
    {
        return static_cast<RenderStages>(static_cast<std::underlying_type_t<RenderStages>>(a) ^ static_cast<std::underlying_type_t<RenderStages>>(b));
    }
    [[nodiscard]] inline constexpr RenderStages operator~(const RenderStages a) noexcept
    {
        return static_cast<RenderStages>(~static_cast<std::underlying_type_t<RenderStages>>(a));
    }
    inline constexpr RenderStages& operator&=(RenderStages& a, const RenderStages b) noexcept
    {
        return a = static_cast<RenderStages>(static_cast<std::underlying_type_t<RenderStages>>(a) & static_cast<std::underlying_type_t<RenderStages>>(b));
    }
    inline constexpr RenderStages& operator|=(RenderStages& a, const RenderStages b) noexcept
    {
        return a = static_cast<RenderStages>(static_cast<std::underlying_type_t<RenderStages>>(a) | static_cast<std::underlying_type_t<RenderStages>>(b));
    }
    inline constexpr RenderStages& operator^=(RenderStages& a, const RenderStages b) noexcept
    {
        return a = static_cast<RenderStages>(static_cast<std::underlying_type_t<RenderStages>>(a) ^ static_cast<std::underlying_type_t<RenderStages>>(b));
    }

    template<class T, std::size_t N>
    inline auto convertToArray(const T (&objects)[N]) noexcept
    {
        std::array<id, N> result;
        for (std::size_t i = 0; i < N; ++i) result[i] = objects[i].get();
        return result;
    }

    class RenderCommandEncoder final: public CommandEncoder
    {
    public:
        METALPP_PRIVATE_SEL(setRenderPipelineState_, "setRenderPipelineState:");
        METALPP_PRIVATE_SEL(setVertexBuffer_offset_atIndex_, "setVertexBuffer:offset:atIndex:");
        METALPP_PRIVATE_SEL(setVertexTexture_atIndex_, "setVertexTexture:atIndex:");
        METALPP_PRIVATE_SEL(setVertexTextures_withRange_, "setVertexTextures:withRange:");
        METALPP_PRIVATE_SEL(setVertexSamplerState_atIndex_, "setVertexSamplerState:atIndex:");
        METALPP_PRIVATE_SEL(setVertexSamplerStates_withRange_, "setVertexSamplerStates:withRange:");
        METALPP_PRIVATE_SEL(setViewport_, "setViewport:");
        METALPP_PRIVATE_SEL(setFrontFacingWinding_, "setFrontFacingWinding:");
        METALPP_PRIVATE_SEL(setCullMode_, "setCullMode:");
        METALPP_PRIVATE_SEL(setDepthClipMode_, "setDepthClipMode:");
        METALPP_PRIVATE_SEL(setDepthBias_slopeScale_clamp_, "setDepthBias:slopeScale:clamp:");
        METALPP_PRIVATE_SEL(setScissorRect_, "setScissorRect:");
        METALPP_PRIVATE_SEL(setTriangleFillMode_, "setTriangleFillMode:");
        METALPP_PRIVATE_SEL(setFragmentBuffer_offset_atIndex_, "setFragmentBuffer:offset:atIndex:");
        METALPP_PRIVATE_SEL(setFragmentTexture_atIndex_, "setFragmentTexture:atIndex:");
        METALPP_PRIVATE_SEL(setFragmentTextures_withRange_, "setFragmentTextures:withRange:");
        METALPP_PRIVATE_SEL(setFragmentSamplerState_atIndex_, "setFragmentSamplerState:atIndex:");
        METALPP_PRIVATE_SEL(setFragmentSamplerStates_withRange_, "setFragmentSamplerStates:withRange:");
        METALPP_PRIVATE_SEL(setDepthStencilState_, "setDepthStencilState:");
        METALPP_PRIVATE_SEL(drawPrimitives_vertexStart_vertexCount_, "drawPrimitives:vertexStart:vertexCount:");
        METALPP_PRIVATE_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_, "drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:");
        METALPP_PRIVATE_SEL(updateFence_afterStages_, "updateFence:afterStages:");
        METALPP_PRIVATE_SEL(waitForFence_beforeStages_, "waitForFence:beforeStages:");

        using CommandEncoder::CommandEncoder;
        using CommandEncoder::operator=;

        RenderCommandEncoder() = delete;

        void setRenderPipelineState(const RenderPipelineState& pipelineState) noexcept
        {
            sendMessage(METALPP_SEL(setRenderPipelineState_), pipelineState.get());
        }

        void setVertexBuffer(const Buffer& buffer, const ns::UInteger offset,
                             const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setVertexBuffer_offset_atIndex_),
                        buffer.get(),
                        offset,
                        index);
        }

        void setVertexTexture(const Texture& texture,
                              const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setVertexTexture_atIndex_),
                        texture.get(),
                        index);
        }

        template<std::size_t N>
        void setVertexTextures(const std::reference_wrapper<Texture> (&textures)[N],
                               const ns::Range& range) noexcept
        {
            sendMessage(METALPP_SEL(setVertexTextures_withRange_),
                        convertToArray(textures).data(),
                        range);
        }

        void setVertexSamplerState(const SamplerState& sampler,
                                   const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setVertexSamplerState_atIndex_),
                        sampler.get(),
                        index);
        }

        template<std::size_t N>
        void setVertexSamplerStates(const std::reference_wrapper<SamplerState> (&samplers)[N],
                                    const ns::Range& range) noexcept
        {
            sendMessage(METALPP_SEL(setVertexSamplerStates_withRange_),
                        convertToArray(samplers).data(),
                        range);
        }

        void setViewport(const Viewport& viewport) noexcept
        {
            sendMessage(METALPP_SEL(setViewport_), viewport);
        }

        void setFrontFacingWinding(const Winding winding) noexcept
        {
            sendMessage(METALPP_SEL(setFrontFacingWinding_), winding);
        }

        void setCullMode(const CullMode cullMode) noexcept
        {
            sendMessage(METALPP_SEL(setCullMode_), cullMode);
        }

        void setDepthClipMode(const DepthClipMode depthClipMode) noexcept API_AVAILABLE(macos(10.11), ios(11.0))
        {
            sendMessage(METALPP_SEL(setDepthClipMode_), depthClipMode);
        }

        void setDepthBias(const float depthBias,
                          const float slopeScale,
                          const float clamp) noexcept
        {
            sendMessage(METALPP_SEL(setDepthBias_slopeScale_clamp_), depthBias, slopeScale, clamp);
        }

        void setScissorRect(const ScissorRect& rect) noexcept
        {
            sendMessage(METALPP_SEL(setScissorRect_), rect);
        }

        void setTriangleFillMode(const TriangleFillMode fillMode) noexcept
        {
            sendMessage(METALPP_SEL(setTriangleFillMode_), fillMode);
        }

        void setFragmentBuffer(const Buffer& buffer,
                               const ns::UInteger offset,
                               const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentBuffer_offset_atIndex_),
                        buffer.get(),
                        offset,
                        index);
        }

        void setFragmentTexture(const Texture& texture,
                                const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentTexture_atIndex_),
                        texture.get(),
                        index);
        }

        template<std::size_t N>
        void setFragmentTextures(const std::reference_wrapper<Texture> (&textures)[N],
                                 const ns::Range& range) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentTextures_withRange_),
                        convertToArray(textures).data(),
                        range);
        }

        void setFragmentSamplerState(const SamplerState& sampler,
                                     const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentSamplerState_atIndex_),
                        sampler.get(),
                        index);
        }

        template<std::size_t N>
        void setFragmentSamplerStates(const std::reference_wrapper<SamplerState> (&samplers)[N],
                                      const ns::Range& range) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentSamplerStates_withRange_),
                        convertToArray(samplers).data(),
                        range);
        }

        void setDepthStencilState(const DepthStencilState& depthStencilState)
        {
            sendMessage(METALPP_SEL(setDepthStencilState_), depthStencilState.get());
        }

        void drawPrimitives(const PrimitiveType primitiveType,
                            const ns::UInteger vertexStart,
                            const ns::UInteger vertexCount) noexcept
        {
            sendMessage(METALPP_SEL(drawPrimitives_vertexStart_vertexCount_),
                        primitiveType,
                        vertexStart,
                        vertexCount);
        }

        void drawIndexedPrimitives(const PrimitiveType primitiveType,
                                   const ns::UInteger indexCount,
                                   const IndexType indexType,
                                   const Buffer& indexBuffer,
                                   const ns::UInteger indexBufferOffset) noexcept
        {
            sendMessage(METALPP_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_),
                        primitiveType,
                        indexCount,
                        indexType,
                        indexBuffer.get(),
                        indexBufferOffset);
        }

        void updateFence(const Fence& fence, const RenderStages stages) noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            sendMessage(METALPP_SEL(updateFence_afterStages_), fence.get(), stages);
        }

        void waitForFence(const Fence& fence, const RenderStages stages) noexcept API_AVAILABLE(macos(10.13), ios(10.0))
        {
            sendMessage(METALPP_SEL(waitForFence_beforeStages_), fence.get(), stages);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
