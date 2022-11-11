#ifndef METALPP_METAL_VERTEXDESCRIPTOR_HPP
#define METALPP_METAL_VERTEXDESCRIPTOR_HPP

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

    class VertexDescriptor final: public ns::Object
    {
        inline static const auto cls = objc_lookUpClass("MTLVertexDescriptor");

        inline static const auto resetSel = sel_registerName("reset");

    public:
        VertexDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, allocSel), initSel)}
        {
        }

        void reset() noexcept
        {
            objc::sendMessage(*this, resetSel);
        }
    };
}

#endif