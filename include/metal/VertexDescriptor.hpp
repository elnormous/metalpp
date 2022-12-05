#ifndef METALPP_METAL_VERTEXDESCRIPTOR_HPP
#define METALPP_METAL_VERTEXDESCRIPTOR_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../objc/Runtime.hpp"

namespace mtl
{
    enum class VertexFormat: ns::UInteger
    {
        Invalid = 0,

        UChar2 = 1,
        UChar3 = 2,
        UChar4 = 3,

        Char2 = 4,
        Char3 = 5,
        Char4 = 6,

        UChar2Normalized = 7,
        UChar3Normalized = 8,
        UChar4Normalized = 9,

        Char2Normalized = 10,
        Char3Normalized = 11,
        Char4Normalized = 12,

        UShort2 = 13,
        UShort3 = 14,
        UShort4 = 15,

        Short2 = 16,
        Short3 = 17,
        Short4 = 18,

        UShort2Normalized = 19,
        UShort3Normalized = 20,
        UShort4Normalized = 21,

        Short2Normalized = 22,
        Short3Normalized = 23,
        Short4Normalized = 24,

        Half2 = 25,
        Half3 = 26,
        Half4 = 27,

        Float = 28,
        Float2 = 29,
        Float3 = 30,
        Float4 = 31,

        Int = 32,
        Int2 = 33,
        Int3 = 34,
        Int4 = 35,

        UInt = 36,
        UInt2 = 37,
        UInt3 = 38,
        UInt4 = 39,

        Int1010102Normalized = 40,
        UInt1010102Normalized = 41,

        UChar4Normalized_BGRA API_AVAILABLE(macos(10.13), ios(11.0)) = 42,

        UChar API_AVAILABLE(macos(10.13), ios(11.0)) = 45,
        Char API_AVAILABLE(macos(10.13), ios(11.0)) = 46,
        UCharNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 47,
        CharNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 48,

        UShort API_AVAILABLE(macos(10.13), ios(11.0)) = 49,
        Short API_AVAILABLE(macos(10.13), ios(11.0)) = 50,
        UShortNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 51,
        ShortNormalized API_AVAILABLE(macos(10.13), ios(11.0)) = 52,

        Half API_AVAILABLE(macos(10.13), ios(11.0)) = 53,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class VertexStepFunction: ns::UInteger
    {
        Constant = 0,
        PerVertex = 1,
        PerInstance = 2,
        PerPatch API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
        PerPatchControlPoint API_AVAILABLE(macos(10.12), ios(10.0)) = 4,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexBufferLayoutDescriptor final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(stride, "stride");
        METALPP_PRIVATE_SEL(setStride_, "setStride:");
        METALPP_PRIVATE_SEL(stepFunction, "stepFunction");
        METALPP_PRIVATE_SEL(setStepFunction_, "setStepFunction:");
        METALPP_PRIVATE_SEL(stepRate, "stepRate");
        METALPP_PRIVATE_SEL(setStepRate_, "setStepRate:");

        VertexBufferLayoutDescriptor() = delete;

        [[nodiscard]] auto stride() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(stride));
        }

        void setStride(ns::UInteger stride) noexcept
        {
            sendMessage(METALPP_SEL(setStride_), stride);
        }

        [[nodiscard]] auto stepFunction() const noexcept
        {
            return sendMessage<VertexStepFunction>(METALPP_SEL(stepFunction));
        }

        void setStepFunction(VertexStepFunction stepFunction) noexcept
        {
            sendMessage(METALPP_SEL(setStepFunction_), stepFunction);
        }

        [[nodiscard]] auto stepRate() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(stepRate));
        }

        void setStepRate(ns::UInteger stepRate) noexcept
        {
            sendMessage(METALPP_SEL(setStepRate_), stepRate);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexBufferLayoutDescriptorArray final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(objectAtIndexedSubscript_, "objectAtIndexedSubscript:");

        VertexBufferLayoutDescriptorArray() = delete;

        [[nodiscard]] auto objectAtIndexedSubscript(const ns::UInteger index) const noexcept
        {
            return getRetained<VertexBufferLayoutDescriptor>(METALPP_SEL(objectAtIndexedSubscript_), index);
        }

        [[nodiscard]] auto operator[](const ns::UInteger index) const noexcept
        {
            return objectAtIndexedSubscript(index);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexAttributeDescriptor final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(format, "format");
        METALPP_PRIVATE_SEL(setFormat_, "setFormat:");
        METALPP_PRIVATE_SEL(offset, "offset");
        METALPP_PRIVATE_SEL(setOffset_, "setOffset:");
        METALPP_PRIVATE_SEL(bufferIndex, "bufferIndex");
        METALPP_PRIVATE_SEL(setBufferIndex_, "setBufferIndex:");

        VertexAttributeDescriptor() = delete;

        [[nodiscard]] auto format() const noexcept
        {
            return sendMessage<VertexFormat>(METALPP_SEL(format));
        }

        void setFormat(VertexFormat vertexFormat) noexcept
        {
            sendMessage(METALPP_SEL(setFormat_), vertexFormat);
        }

        [[nodiscard]] auto offset() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(offset));
        }

        void setOffset(ns::UInteger offset) noexcept
        {
            sendMessage(METALPP_SEL(setOffset_), offset);
        }

        [[nodiscard]] auto bufferIndex() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(bufferIndex));
        }

        void setBufferIndex(ns::UInteger bufferIndex) noexcept
        {
            sendMessage(METALPP_SEL(setBufferIndex_), bufferIndex);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexAttributeDescriptorArray final: public ns::Object
    {
    public:
        METALPP_PRIVATE_SEL(objectAtIndexedSubscript_, "objectAtIndexedSubscript:");

        VertexAttributeDescriptorArray() = delete;

        [[nodiscard]] auto objectAtIndexedSubscript(const ns::UInteger index) const noexcept
        {
            return getRetained<VertexAttributeDescriptor>(METALPP_SEL(objectAtIndexedSubscript_), index);
        }

        [[nodiscard]] auto operator[](const ns::UInteger index) const noexcept
        {
            return objectAtIndexedSubscript(index);
        }
    };

    class VertexDescriptor final: public ns::Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("MTLVertexDescriptor");

        METALPP_PRIVATE_SEL(layouts, "layouts");
        METALPP_PRIVATE_SEL(attributes, "attributes");
        METALPP_PRIVATE_SEL(reset, "reset");

        using Object::Object;

        VertexDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {
        }

        [[nodiscard]] auto layouts() const noexcept
        {
            return getRetained<VertexBufferLayoutDescriptorArray>(METALPP_SEL(layouts));
        }

        [[nodiscard]] auto attributes() const noexcept
        {
            return getRetained<VertexAttributeDescriptorArray>(METALPP_SEL(attributes));
        }

        void reset() noexcept
        {
            sendMessage(METALPP_SEL(reset));
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
