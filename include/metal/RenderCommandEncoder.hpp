#ifndef METALPP_METAL_RENDERCOMMANDENCODER_HPP
#define METALPP_METAL_RENDERCOMMANDENCODER_HPP

namespace mtl
{
    struct ScissorRect
    {
        NSUInteger x, y, width, height;
    };

    struct Viewport
    {
        double originX, originY, width, height, znear, zfar;
    };
}

#endif
