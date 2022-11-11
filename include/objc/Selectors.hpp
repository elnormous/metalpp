#ifndef METALPP_OBJC_SELECTORS_HPP
#define METALPP_OBJC_SELECTORS_HPP

#include <objc/message.h>

namespace objc
{
    inline const auto allocSel = sel_registerName("alloc");
    inline const auto initSel = sel_registerName("init");
    inline const auto retainSel = sel_registerName("retain");
    inline const auto releaseSel = sel_registerName("release");
    inline const auto retainCountSel = sel_registerName("retainCount");

    inline const auto objectAtIndexedSubscript_Sel = sel_registerName("objectAtIndexedSubscript:");
    inline const auto setObject_atIndexedSubscript_Sel = sel_registerName("setObject:atIndexedSubscript:");

    inline const auto drainSel = sel_registerName("drain");

    inline const auto codeSel = sel_registerName("code");
    inline const auto domainSel = sel_registerName("domain");
    inline const auto localizedDescriptionSel = sel_registerName("localizedDescription");

    inline const auto initWithBytes_length_encoding_Sel = sel_registerName("initWithBytes:length:encoding:");
    inline const auto lengthSel = sel_registerName("length");
    inline const auto characterAtIndex_Sel = sel_registerName("characterAtIndex:");
    inline const auto cStringUsingEncoding_Sel = sel_registerName("cStringUsingEncoding:");

    inline const auto newDefaultLibrarySel = sel_registerName("newDefaultLibrary");
    inline const auto newLibraryWithSource_options_error_Sel = sel_registerName("newLibraryWithSource:options:error:");
    inline const auto nameSel = sel_registerName("name");
    inline const auto newRenderPipelineStateWithDescriptor_error_Sel = sel_registerName("newRenderPipelineStateWithDescriptor:error:");

    inline const auto newFunctionWithName_Sel = sel_registerName("newFunctionWithName:");

    inline const auto labelSel = sel_registerName("label");
    inline const auto setLabel_Sel = sel_registerName("setLabel:");

    inline const auto vertexFunctionSel = sel_registerName("setVertexFunction");
    inline const auto setVertexFunction_Sel = sel_registerName("setVertexFunction:");
    inline const auto fragmentFunctionSel = sel_registerName("fragmentFunction");
    inline const auto setFragmentFunction_Sel = sel_registerName("setFragmentFunction:");
    inline const auto vertexDescriptorSel = sel_registerName("vertexDescriptor");
    inline const auto setVertexDescriptor_Sel = sel_registerName("setVertexDescriptor:");
    inline const auto depthAttachmentPixelFormatSel = sel_registerName("depthAttachmentPixelFormat");
    inline const auto setDepthAttachmentPixelFormat_Sel = sel_registerName("setDepthAttachmentPixelFormat:");
    inline const auto stencilAttachmentPixelFormatSel = sel_registerName("stencilAttachmentPixelFormat");
    inline const auto setStencilAttachmentPixelFormat_Sel = sel_registerName("setStencilAttachmentPixelFormat:");

    inline const auto layoutsSel = sel_registerName("layouts");
    inline const auto attributesSel = sel_registerName("attributes");
    inline const auto resetSel = sel_registerName("reset");

    inline const auto formatSel = sel_registerName("format");
    inline const auto setFormat_Sel = sel_registerName("setFormat:");
    inline const auto offsetSel = sel_registerName("offset");
    inline const auto setOffset_Sel = sel_registerName("setOffset:");
    inline const auto bufferIndexSel = sel_registerName("bufferIndex");
    inline const auto setBufferIndex_Sel = sel_registerName("setBufferIndex:");

    inline const auto strideSel = sel_registerName("stride");
    inline const auto setStride_Sel = sel_registerName("setStride:");
    inline const auto stepFunctionSel = sel_registerName("stepFunction");
    inline const auto setStepFunction_Sel = sel_registerName("setStepFunction:");
    inline const auto stepRateSel = sel_registerName("stepRate");
    inline const auto setStepRate_Sel = sel_registerName("setStepRate:");
}

#endif
