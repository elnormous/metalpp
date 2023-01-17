#ifndef METALPP_METAL_INDIRECTCOMMANDENCODER_HPP
#define METALPP_METAL_INDIRECTCOMMANDENCODER_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"
#include "Buffer.hpp"
#include "ComputePipeline.hpp"
#include "RenderPipeline.hpp"
#include "Types.hpp"

namespace mtl
{
    class IndirectRenderCommand: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(setRenderPipelineState_, "setRenderPipelineState:");
        METALPP_PRIVATE_SEL(setVertexBuffer_offset_atIndex_, "setVertexBuffer:offset:atIndex:");
        METALPP_PRIVATE_SEL(setFragmentBuffer_offset_atIndex_, "setFragmentBuffer:offset:atIndex:");
        METALPP_PRIVATE_SEL(drawPatches_patchStart_patchCount_patchIndexBuffer_patchIndexBufferOffset_instanceCount_baseInstance_tessellationFactorBuffer_tessellationFactorBufferOffset_tessellationFactorBufferInstanceStride_, "drawPatches:patchStart:patchCount:patchIndexBuffer:patchIndexBufferOffset:instanceCount:baseInstance:tessellationFactorBuffer:tessellationFactorBufferOffset:tessellationFactorBufferInstanceStride:");
        METALPP_PRIVATE_SEL(drawIndexedPatches_patchStart_patchCount_patchIndexBuffer_patchIndexBufferOffset_controlPointIndexBuffer_controlPointIndexBufferOffset_instanceCount_baseInstance_tessellationFactorBuffer_tessellationFactorBufferOffset_tessellationFactorBufferInstanceStride_, "drawIndexedPatches:patchStart:patchCount:patchIndexBuffer:patchIndexBufferOffset:controlPointIndexBuffer:controlPointIndexBufferOffset:instanceCount:baseInstance:tessellationFactorBuffer:tessellationFactorBufferOffset:tessellationFactorBufferInstanceStride:");
        METALPP_PRIVATE_SEL(drawPrimitives_vertexStart_vertexCount_instanceCount_baseInstance_, "drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:");
        METALPP_PRIVATE_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_instanceCount_baseVertex_baseInstance_, "drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:baseVertex:baseInstance:");
        METALPP_PRIVATE_SEL(reset, "reset");

        void setRenderPipelineState(const RenderPipelineState& pipelineState) noexcept
        {
            sendMessage(METALPP_SEL(setRenderPipelineState_), pipelineState.get());
        }

        void setVertexBuffer(const Buffer& buffer, const ns::UInteger offset, const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setVertexBuffer_offset_atIndex_), buffer.get(), offset, index);
        }

        void setFragmentBuffer(const Buffer& buffer, const ns::UInteger offset, const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setFragmentBuffer_offset_atIndex_), buffer.get(), offset, index);
        }

        void drawPatches(const ns::UInteger numberOfPatchControlPoints, const ns::UInteger patchStart, const ns::UInteger patchCount, const Buffer& patchIndexBuffer, const ns::UInteger patchIndexBufferOffset, const ns::UInteger instanceCount, const ns::UInteger baseInstance, const Buffer buffer, const ns::UInteger offset, const ns::UInteger instanceStride) noexcept
        {
            sendMessage(METALPP_SEL(drawPatches_patchStart_patchCount_patchIndexBuffer_patchIndexBufferOffset_instanceCount_baseInstance_tessellationFactorBuffer_tessellationFactorBufferOffset_tessellationFactorBufferInstanceStride_),
                        numberOfPatchControlPoints,
                        patchStart,
                        patchCount,
                        patchIndexBuffer.get(),
                        patchIndexBufferOffset,
                        instanceCount,
                        baseInstance,
                        buffer.get(),
                        offset,
                        instanceStride);
        }

        void drawIndexedPatches(const ns::UInteger numberOfPatchControlPoints, const ns::UInteger patchStart, const ns::UInteger patchCount, const Buffer& patchIndexBuffer, const ns::UInteger patchIndexBufferOffset, const Buffer controlPointIndexBuffer, const ns::UInteger controlPointIndexBufferOffset, const ns::UInteger instanceCount, const ns::UInteger baseInstance, const Buffer& buffer, const ns::UInteger offset, const ns::UInteger instanceStride) noexcept
        {
            sendMessage(METALPP_SEL(drawIndexedPatches_patchStart_patchCount_patchIndexBuffer_patchIndexBufferOffset_controlPointIndexBuffer_controlPointIndexBufferOffset_instanceCount_baseInstance_tessellationFactorBuffer_tessellationFactorBufferOffset_tessellationFactorBufferInstanceStride_),
                        numberOfPatchControlPoints,
                        patchStart,
                        patchCount,
                        patchIndexBuffer.get(),
                        patchIndexBufferOffset,
                        controlPointIndexBuffer,
                        controlPointIndexBufferOffset,
                        instanceCount,
                        baseInstance,
                        buffer.get(),
                        offset,
                        instanceStride);
        }

        void drawPrimitives(const PrimitiveType primitiveType, const ns::UInteger vertexStart, const ns::UInteger vertexCount, const ns::UInteger instanceCount, const ns::UInteger baseInstance) noexcept
        {
            sendMessage(METALPP_SEL(drawPrimitives_vertexStart_vertexCount_instanceCount_baseInstance_), primitiveType, vertexStart, vertexCount, instanceCount, baseInstance);
        }

        void drawIndexedPrimitives(const PrimitiveType primitiveType, const ns::UInteger indexCount, const IndexType indexType, const Buffer& indexBuffer, const ns::UInteger indexBufferOffset, const ns::UInteger instanceCount, const ns::Integer baseVertex, const ns::UInteger baseInstance) noexcept
        {
            sendMessage(METALPP_SEL(drawIndexedPrimitives_indexCount_indexType_indexBuffer_indexBufferOffset_instanceCount_baseVertex_baseInstance_),
                        primitiveType,
                        indexCount,
                        indexType,
                        indexBuffer.get(),
                        indexBufferOffset,
                        instanceCount,
                        baseVertex,
                        baseInstance);
        }

        void reset() noexcept
        {
            sendMessage(METALPP_SEL(reset));
        }
    } API_AVAILABLE(macos(10.14), ios(12.0));

    class IndirectComputeCommand: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(setComputePipelineState_, "setComputePipelineState:");
        METALPP_PRIVATE_SEL(setKernelBuffer_offset_atIndex_, "setKernelBuffer:offset:atIndex:");
        METALPP_PRIVATE_SEL(concurrentDispatchThreadgroups_threadsPerThreadgroup_, "concurrentDispatchThreadgroups:threadsPerThreadgroup:");
        METALPP_PRIVATE_SEL(concurrentDispatchThreads_threadsPerThreadgroup_, "concurrentDispatchThreads:threadsPerThreadgroup:");
        METALPP_PRIVATE_SEL(setBarrier, "setBarrier");
        METALPP_PRIVATE_SEL(clearBarrier, "clearBarrier");
        METALPP_PRIVATE_SEL(setImageblockWidth_height_, "setImageblockWidth:height:");
        METALPP_PRIVATE_SEL(reset, "reset");
        METALPP_PRIVATE_SEL(setThreadgroupMemoryLength_atIndex_, "setThreadgroupMemoryLength:atIndex:");
        METALPP_PRIVATE_SEL(setStageInRegion_, "setStageInRegion:");

        void setComputePipelineState(const ComputePipelineState& pipelineState) noexcept API_AVAILABLE(ios(13.0), macos(11.0))
        {
            sendMessage(METALPP_SEL(setComputePipelineState_), pipelineState.get());
        }

        void setKernelBuffer(const Buffer& buffer, const ns::UInteger offset, const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setKernelBuffer_offset_atIndex_), buffer.get(), offset, index);
        }

        void concurrentDispatchThreadgroups(const Size& threadgroupsPerGrid, const Size& threadsPerThreadgroup) noexcept
        {
            sendMessage(METALPP_SEL(concurrentDispatchThreadgroups_threadsPerThreadgroup_), threadgroupsPerGrid, threadsPerThreadgroup);
        }

        void concurrentDispatchThreads(const Size& threadsPerGrid, const Size& threadsPerThreadgroup) noexcept
        {
            sendMessage(METALPP_SEL(concurrentDispatchThreads_threadsPerThreadgroup_), threadsPerGrid, threadsPerThreadgroup);
        }

        void setBarrier() noexcept
        {
            sendMessage(METALPP_SEL(setBarrier));
        }

        void clearBarrier() noexcept
        {
            sendMessage(METALPP_SEL(clearBarrier));
        }

        void setImageblock(const ns::UInteger width, const ns::UInteger height) noexcept API_AVAILABLE(ios(14.0), macos(11.0))
        {
            sendMessage(METALPP_SEL(setImageblockWidth_height_), width, height);
        }

        void reset() noexcept
        {
            sendMessage(METALPP_SEL(reset));
        }

        void setThreadgroupMemoryLength(const ns::UInteger length, const ns::UInteger index) noexcept
        {
            sendMessage(METALPP_SEL(setThreadgroupMemoryLength_atIndex_), length, index);
        }

        void setStageInRegion(const Region& region) noexcept
        {
            sendMessage(METALPP_SEL(setStageInRegion_), region);
        }
    } API_AVAILABLE(ios(13.0), macos(11.0));
}

#endif
