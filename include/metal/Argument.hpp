#ifndef METALPP_METAL_ARGUMENT_HPP
#define METALPP_METAL_ARGUMENT_HPP

#include <os/availability.h>
#include "../objc/Runtime.hpp"

namespace mtl
{
    enum class DataType: ns::UInteger
    {

        None = 0,

        Struct = 1,
        Array  = 2,

        Float  = 3,
        Float2 = 4,
        Float3 = 5,
        Float4 = 6,

        Float2x2 = 7,
        Float2x3 = 8,
        Float2x4 = 9,

        Float3x2 = 10,
        Float3x3 = 11,
        Float3x4 = 12,

        Float4x2 = 13,
        Float4x3 = 14,
        Float4x4 = 15,

        Half  = 16,
        Half2 = 17,
        Half3 = 18,
        Half4 = 19,

        Half2x2 = 20,
        Half2x3 = 21,
        Half2x4 = 22,

        Half3x2 = 23,
        Half3x3 = 24,
        Half3x4 = 25,

        Half4x2 = 26,
        Half4x3 = 27,
        Half4x4 = 28,

        Int  = 29,
        Int2 = 30,
        Int3 = 31,
        Int4 = 32,

        UInt  = 33,
        UInt2 = 34,
        UInt3 = 35,
        UInt4 = 36,

        Short  = 37,
        Short2 = 38,
        Short3 = 39,
        Short4 = 40,

        UShort = 41,
        UShort2 = 42,
        UShort3 = 43,
        UShort4 = 44,

        Char  = 45,
        Char2 = 46,
        Char3 = 47,
        Char4 = 48,

        UChar  = 49,
        UChar2 = 50,
        UChar3 = 51,
        UChar4 = 52,

        Bool  = 53,
        Bool2 = 54,
        Bool3 = 55,
        Bool4 = 56,

        Texture API_AVAILABLE(macos(10.13), ios(11.0)) = 58,
        Sampler API_AVAILABLE(macos(10.13), ios(11.0)) = 59,
        Pointer API_AVAILABLE(macos(10.13), ios(11.0)) = 60,

        R8Unorm         API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 62,
        R8Snorm         API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 63,
        R16Unorm        API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 64,
        R16Snorm        API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 65,
        RG8Unorm        API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 66,
        RG8Snorm        API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 67,
        RG16Unorm       API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 68,
        RG16Snorm       API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 69,
        RGBA8Unorm      API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 70,
        RGBA8Unorm_sRGB API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 71,
        RGBA8Snorm      API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 72,
        RGBA16Unorm     API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 73,
        RGBA16Snorm     API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 74,
        RGB10A2Unorm    API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 75,
        RG11B10Float    API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 76,
        RGB9E5Float     API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5)) = 77,
        RenderPipeline  API_AVAILABLE(macos(10.14), ios(13.0)) = 78,
        ComputePipeline API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(13.0)) = 79,
        IndirectCommandBuffer   API_AVAILABLE(macos(10.14), ios(12.0)) = 80,
        Long  API_AVAILABLE(macos(12.0), ios(14.0)) = 81,
        Long2 API_AVAILABLE(macos(12.0), ios(14.0)) = 82,
        Long3 API_AVAILABLE(macos(12.0), ios(14.0)) = 83,
        Long4 API_AVAILABLE(macos(12.0), ios(14.0)) = 84,

        ULong  API_AVAILABLE(macos(12.0), ios(14.0)) = 85,
        ULong2 API_AVAILABLE(macos(12.0), ios(14.0)) = 86,
        ULong3 API_AVAILABLE(macos(12.0), ios(14.0)) = 87,
        ULong4 API_AVAILABLE(macos(12.0), ios(14.0)) = 88,
        VisibleFunctionTable API_AVAILABLE(macos(11.0), ios(14.0)) = 115,
        IntersectionFunctionTable API_AVAILABLE(macos(11.0), ios(14.0)) = 116,
        PrimitiveAccelerationStructure API_AVAILABLE(macos(11.0), ios(14.0)) = 117,
        InstanceAccelerationStructure API_AVAILABLE(macos(11.0), ios(14.0)) = 118,
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class BindingType: ns::Integer
    {
        Buffer = 0,
        ThreadgroupMemory = 1,
        Texture = 2,
        Sampler = 3,
        ImageblockData = 16,
        Imageblock = 17,
        VisibleFunctionTable = 24,
        PrimitiveAccelerationStructure = 25,
        InstanceAccelerationStructure = 26,
        IntersectionFunctionTable = 27,
        ObjectPayload = 34,
    } API_AVAILABLE(macos(11.0), ios(14.0));

    enum class ArgumentType: ns::UInteger
    {

        Buffer = 0,
        ThreadgroupMemory= 1,
        Texture = 2,
        Sampler = 3,

        ImageblockData API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5))     = 16,
        Imageblock API_AVAILABLE(macos(11.0), macCatalyst(14.0), ios(11.0), tvos(14.5))         = 17,
        VisibleFunctionTable API_AVAILABLE(macos(11.0), ios(14.0)) = 24,
        PrimitiveAccelerationStructure API_AVAILABLE(macos(11.0), ios(14.0)) = 25,
        InstanceAccelerationStructure API_AVAILABLE(macos(11.0), ios(14.0)) = 26,
        IntersectionFunctionTable API_AVAILABLE(macos(11.0), ios(14.0)) = 27,
    } API_DEPRECATED_WITH_REPLACEMENT("MTLBindingType", macos(10.11, 13.0), ios(8.0, 16.0));

    enum class ArgumentAccess: ns::UInteger
    {
        ReadOnly   = 0,
        ReadWrite  = 1,
        WriteOnly  = 2,
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
