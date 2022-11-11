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

    inline const auto objectAtIndexedSubscriptSel = sel_registerName("objectAtIndexedSubscript");
    inline const auto setObjectAtIndexedSubscriptSel = sel_registerName("setObject:atIndexedSubscript:");

    inline const auto drainSel = sel_registerName("drain");

    inline const auto codeSel = sel_registerName("code");
    inline const auto domainSel = sel_registerName("domain");
    inline const auto localizedDescriptionSel = sel_registerName("localizedDescription");

    inline const auto initWithBytesLengthEncodingSel = sel_registerName("initWithBytes:length:encoding:");
    inline const auto lengthSel = sel_registerName("length");
    inline const auto characterAtIndexSel = sel_registerName("characterAtIndex:");
    inline const auto cStringUsingEncodingSel = sel_registerName("cStringUsingEncoding:");

    inline const auto labelSel = sel_registerName("label");

    inline const auto newDefaultLibrarySel = sel_registerName("newDefaultLibrary");
    inline const auto newLibraryWithSourceOptionsErrorSel = sel_registerName("newLibraryWithSource:options:error:");
    inline const auto nameSel = sel_registerName("name");
    inline const auto newRenderPipelineStateWithDescriptorErrorSel = sel_registerName("newRenderPipelineStateWithDescriptor:error:");

    inline const auto newFunctionWithNameSel = sel_registerName("newFunctionWithName:");

    inline const auto setLabelSel = sel_registerName("setLabel:");
    inline const auto setVertexFunctionSel = sel_registerName("setVertexFunction:");
    inline const auto setFragmentFunctionSel = sel_registerName("setFragmentFunction:");
    inline const auto setVertexDescriptorSel = sel_registerName("setVertexDescriptor:");
    inline const auto setDepthAttachmentPixelFormatSel = sel_registerName("setDepthAttachmentPixelFormat:");
    inline const auto setStencilAttachmentPixelFormatSel = sel_registerName("setStencilAttachmentPixelFormat:");

    inline const auto layoutsSel = sel_registerName("layouts");
    inline const auto attributesSel = sel_registerName("attributes");
    inline const auto resetSel = sel_registerName("reset");
}

#endif
