#ifndef METALPP_OBJC_SELECTORS_HPP
#define METALPP_OBJC_SELECTORS_HPP

#include <objc/message.h>

namespace objc
{
    namespace sel
    {
        inline const auto alloc = sel_registerName("alloc");
        inline const auto init = sel_registerName("init");
        inline const auto retain = sel_registerName("retain");
        inline const auto release = sel_registerName("release");
        inline const auto retainCount = sel_registerName("retainCount");
        
        inline const auto objectAtIndexedSubscript_ = sel_registerName("objectAtIndexedSubscript:");
        inline const auto setObject_atIndexedSubscript_ = sel_registerName("setObject:atIndexedSubscript:");
        
        inline const auto drain = sel_registerName("drain");
        
        inline const auto code = sel_registerName("code");
        inline const auto domain = sel_registerName("domain");
        inline const auto localizedDescription = sel_registerName("localizedDescription");
        
        inline const auto initWithBytes_length_encoding_ = sel_registerName("initWithBytes:length:encoding:");
        inline const auto length = sel_registerName("length");
        inline const auto characterAtIndex_ = sel_registerName("characterAtIndex:");
        inline const auto cStringUsingEncoding_ = sel_registerName("cStringUsingEncoding:");
        
        inline const auto newDefaultLibrary = sel_registerName("newDefaultLibrary");
        inline const auto newLibraryWithSource_options_error_ = sel_registerName("newLibraryWithSource:options:error:");
        inline const auto name = sel_registerName("name");
        inline const auto newRenderPipelineStateWithDescriptor_error_ = sel_registerName("newRenderPipelineStateWithDescriptor:error:");
        
        inline const auto newFunctionWithName_ = sel_registerName("newFunctionWithName:");
        
        inline const auto label = sel_registerName("label");
        inline const auto setLabel_ = sel_registerName("setLabel:");
        
        inline const auto vertexFunction = sel_registerName("setVertexFunction");
        inline const auto setVertexFunction_ = sel_registerName("setVertexFunction:");
        inline const auto fragmentFunction = sel_registerName("fragmentFunction");
        inline const auto setFragmentFunction_ = sel_registerName("setFragmentFunction:");
        inline const auto vertexDescriptor = sel_registerName("vertexDescriptor");
        inline const auto setVertexDescriptor_ = sel_registerName("setVertexDescriptor:");
        inline const auto depthAttachmentPixelFormat = sel_registerName("depthAttachmentPixelFormat");
        inline const auto setDepthAttachmentPixelFormat_ = sel_registerName("setDepthAttachmentPixelFormat:");
        inline const auto stencilAttachmentPixelFormat = sel_registerName("stencilAttachmentPixelFormat");
        inline const auto setStencilAttachmentPixelFormat_ = sel_registerName("setStencilAttachmentPixelFormat:");
        
        inline const auto layouts = sel_registerName("layouts");
        inline const auto attributes = sel_registerName("attributes");
        inline const auto reset = sel_registerName("reset");
        
        inline const auto format = sel_registerName("format");
        inline const auto setFormat_ = sel_registerName("setFormat:");
        inline const auto offset = sel_registerName("offset");
        inline const auto setOffset_ = sel_registerName("setOffset:");
        inline const auto bufferIndex = sel_registerName("bufferIndex");
        inline const auto setBufferIndex_ = sel_registerName("setBufferIndex:");
        
        inline const auto stride = sel_registerName("stride");
        inline const auto setStride_ = sel_registerName("setStride:");
        inline const auto stepFunction = sel_registerName("stepFunction");
        inline const auto setStepFunction_ = sel_registerName("setStepFunction:");
        inline const auto stepRate = sel_registerName("stepRate");
        inline const auto setStepRate_ = sel_registerName("setStepRate:");
    }
}

#endif
