#ifndef METALPP_METAL_VERTEXDESCRIPTOR_HPP
#define METALPP_METAL_VERTEXDESCRIPTOR_HPP

#include <objc/NSObjCRuntime.h>
#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/Selectors.hpp"
#include "Selectors.hpp"

namespace mtl
{
    enum class VertexFormat: NSUInteger
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

    enum class VertexStepFunction: NSUInteger
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
        VertexBufferLayoutDescriptor() = delete;

        [[nodiscard]] NSUInteger stride() const noexcept
        {
            return sendMessage<NSUInteger>(sel::stride);
        }

        void setStride(NSUInteger stride) noexcept
        {
            sendMessage(sel::setStride_, stride);
        }

        [[nodiscard]] VertexStepFunction stepFunction() const noexcept
        {
            return sendMessage<VertexStepFunction>(sel::stepFunction);
        }

        void setStepFunction(VertexStepFunction stepFunction) noexcept
        {
            sendMessage(sel::setStepFunction_, stepFunction);
        }

        [[nodiscard]] NSUInteger stepRate() const noexcept
        {
            return sendMessage<NSUInteger>(sel::stepRate);
        }

        void setStepRate(NSUInteger stepRate) noexcept
        {
            sendMessage(sel::setStepRate_, stepRate);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexBufferLayoutDescriptorArray final: public ns::Object
    {
    public:
        VertexBufferLayoutDescriptorArray() = delete;

        [[nodiscard]] VertexBufferLayoutDescriptor operator[](const NSUInteger index) const noexcept
        {
            return objectAtIndexedSubscript(index);
        }

        [[nodiscard]] VertexBufferLayoutDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            return getRetained<VertexBufferLayoutDescriptor>(ns::sel::objectAtIndexedSubscript_, index);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexAttributeDescriptor final: public ns::Object
    {
    public:
        VertexAttributeDescriptor() = delete;

        [[nodiscard]] VertexFormat format() const noexcept
        {
            return sendMessage<VertexFormat>(sel::format);
        }

        void setFormat(VertexFormat vertexFormat) noexcept
        {
            sendMessage(sel::setFormat_, vertexFormat);
        }

        [[nodiscard]] NSUInteger offset() const noexcept
        {
            return sendMessage<NSUInteger>(sel::offset);
        }

        void setOffset(NSUInteger offset) noexcept
        {
            sendMessage(sel::setOffset_, offset);
        }

        [[nodiscard]] NSUInteger bufferIndex() const noexcept
        {
            return sendMessage<NSUInteger>(sel::bufferIndex);
        }

        void setBufferIndex(NSUInteger bufferIndex) noexcept
        {
            sendMessage(sel::setBufferIndex_, bufferIndex);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class VertexAttributeDescriptorArray final: public ns::Object
    {
    public:
        VertexAttributeDescriptorArray() = delete;

        [[nodiscard]] VertexAttributeDescriptor operator[](const NSUInteger index) const noexcept
        {
            return objectAtIndexedSubscript(index);
        }

        [[nodiscard]] VertexAttributeDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            return getRetained<VertexAttributeDescriptor>(ns::sel::objectAtIndexedSubscript_, index);
        }
    };

    class VertexDescriptor final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLVertexDescriptor");
    public:
        VertexDescriptor() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        VertexDescriptor(const id p) noexcept: Object{p} {}

        [[nodiscard]] VertexBufferLayoutDescriptorArray layouts() const noexcept
        {
            return getRetained<VertexBufferLayoutDescriptorArray>(sel::layouts);
        }

        [[nodiscard]] VertexAttributeDescriptorArray attributes() const noexcept
        {
            return getRetained<VertexAttributeDescriptorArray>(sel::attributes);
        }

        void reset() noexcept
        {
            sendMessage(sel::reset);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
