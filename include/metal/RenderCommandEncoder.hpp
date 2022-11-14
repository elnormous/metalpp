#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

#include <objc/NSObjCRuntime.h>

namespace mtl
{
    enum class PrimitiveType: NSUInteger
    {
        Point = 0,
        Line = 1,
        LineStrip = 2,
        Triangle = 3,
        TriangleStrip = 4,
    };

    enum class VisibilityResultMode: NSUInteger
    {
        Disabled = 0,
        Boolean = 1,
        Counting = 2,
    };

    struct ScissorRect
    {
        NSUInteger x, y, width, height;
    };

    struct Viewport
    {
        double originX, originY, width, height, znear, zfar;
    };

    enum class CullMode: NSUInteger
    {
        None = 0,
        Front = 1,
        Back = 2,
    };

    enum class Winding: NSUInteger
    {
        Clockwise = 0,
        CounterClockwise = 1,
    };

    enum class DepthClipMode: NSUInteger
    {
        Clip = 0,
        Clamp = 1,
    };

    enum class TriangleFillMode: NSUInteger
    {
        Fill = 0,
        Lines = 1,
    };
}

#endif
