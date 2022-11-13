#ifndef METALPP_METAL_VERTEXDESCRIPTOR_HPP
#define METALPP_METAL_VERTEXDESCRIPTOR_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "../foundation/Selectors.hpp"
#include "Classes.hpp"
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

        UChar4Normalized_BGRA = 42,

        UChar = 45,
        Char = 46,
        UCharNormalized = 47,
        CharNormalized = 48,

        UShort = 49,
        Short = 50,
        UShortNormalized = 51,
        ShortNormalized = 52,

        Half = 53,
    };

    enum class VertexStepFunction: NSUInteger
    {
        Constant = 0,
        PerVertex = 1,
        PerInstance = 2,
        PerPatch = 3,
        PerPatchControlPoint = 4,
    };

    class VertexBufferLayoutDescriptor final: public ns::Object
    {
    public:
        VertexBufferLayoutDescriptor(const id p) noexcept: Object{p} {}

        NSUInteger stride() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::stride);
        }

        void setStride(NSUInteger stride) noexcept
        {
            objc::sendMessage(*this, sel::setStride_, stride);
        }

        VertexStepFunction stepFunction() const noexcept
        {
            return objc::sendMessage<VertexStepFunction>(*this, sel::stepFunction);
        }

        void setStepFunction(VertexStepFunction stepFunction) noexcept
        {
            objc::sendMessage(*this, sel::setStepFunction_, stepFunction);
        }

        NSUInteger stepRate() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::stepRate);
        }

        void setStepRate(NSUInteger stepRate) noexcept
        {
            objc::sendMessage(*this, sel::setStepRate_, stepRate);
        }
    };

    class VertexBufferLayoutDescriptorArray final: public ns::Object
    {
    public:
        VertexBufferLayoutDescriptorArray(const id p) noexcept: Object{p} {}

        VertexBufferLayoutDescriptor operator[](const std::size_t index) const noexcept
        {
            return objectAtIndexedSubscript(static_cast<NSUInteger>(index));
        }

        VertexBufferLayoutDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndexedSubscript_,
                                                    index);
            return VertexBufferLayoutDescriptor{objc::sendMessage<id>(object, ns::sel::retain)};
        }
    };

    class VertexAttributeDescriptor final: public ns::Object
    {
    public:
        VertexAttributeDescriptor(const id p) noexcept: Object{p} {}

        VertexFormat format() const noexcept
        {
            return objc::sendMessage<VertexFormat>(*this, sel::format);
        }

        void setFormat(VertexFormat vertexFormat) noexcept
        {
            objc::sendMessage(*this, sel::setFormat_, vertexFormat);
        }

        NSUInteger offset() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::offset);
        }

        void setOffset(NSUInteger offset) noexcept
        {
            objc::sendMessage(*this, sel::setOffset_, offset);
        }

        NSUInteger bufferIndex() const noexcept
        {
            return objc::sendMessage<NSUInteger>(*this, sel::bufferIndex);
        }

        void setBufferIndex(NSUInteger bufferIndex) noexcept
        {
            objc::sendMessage(*this, sel::setBufferIndex_, bufferIndex);
        }
    };

    class VertexAttributeDescriptorArray final: public ns::Object
    {
    public:
        VertexAttributeDescriptorArray(const id p) noexcept: Object{p} {}

        VertexAttributeDescriptor operator[](const std::size_t index) const noexcept
        {
            return objectAtIndexedSubscript(static_cast<NSUInteger>(index));
        }

        VertexAttributeDescriptor objectAtIndexedSubscript(const NSUInteger index) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectAtIndexedSubscript_,
                                                    index);
            return VertexAttributeDescriptor{objc::sendMessage<id>(object, ns::sel::retain)};
        }
    };

    class VertexDescriptor final: public ns::Object
    {
    public:
        VertexDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(mtl::cls::vertexDescriptor, ns::sel::alloc), ns::sel::init)}
        {
        }

        VertexDescriptor(const id p) noexcept: Object{p} {}

        VertexBufferLayoutDescriptorArray layouts() const noexcept
        {
            const id layouts = objc::sendMessage<id>(*this, sel::layouts);
            return VertexBufferLayoutDescriptorArray{objc::sendMessage<id>(layouts, ns::sel::retain)};
        }

        VertexAttributeDescriptorArray attributes() const noexcept
        {
            const id attributes = objc::sendMessage<id>(*this, sel::attributes);
            return VertexAttributeDescriptorArray{objc::sendMessage<id>(attributes, ns::sel::retain)};
        }

        void reset() noexcept
        {
            objc::sendMessage(*this, sel::reset);
        }
    };
}

#endif
