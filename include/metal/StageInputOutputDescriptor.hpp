#ifndef METALPP_METAL_STAGEINPUTOUTPUTDESCRIPTOR_HPP
#define METALPP_METAL_STAGEINPUTOUTPUTDESCRIPTOR_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"

namespace mtl
{
    enum class AttributeFormat: ns::UInteger
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
    } API_AVAILABLE(macos(10.12), ios(10.0));

    enum class IndexType: ns::UInteger
    {
        UInt16 = 0,
        UInt32 = 1,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class StepFunction: ns::UInteger
    {
        Constant = 0,

        // vertex functions only
        PerVertex = 1,
        PerInstance = 2,
        PerPatch API_AVAILABLE(macos(10.12), ios(10.0)) = 3,
        PerPatchControlPoint API_AVAILABLE(macos(10.12), ios(10.0)) = 4,

        // compute functions only
        ThreadPositionInGridX = 5,
        ThreadPositionInGridY = 6,
        ThreadPositionInGridXIndexed = 7,
        ThreadPositionInGridYIndexed = 8,
    } API_AVAILABLE(macos(10.12), ios(10.0));
}

#endif
