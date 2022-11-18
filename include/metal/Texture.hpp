#ifndef METALPP_METAL_TEXTURE_HPP
#define METALPP_METAL_TEXTURE_HPP

#include <os/availability.h>
#include "Classes.hpp"
#include "Resource.hpp"

namespace mtl
{
    class TextureDescriptor final: public ns::Object
    {
    public:
        TextureDescriptor():
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls::textureDescriptor, ns::sel::alloc), ns::sel::init)}
        {
        }

    } API_AVAILABLE(macos(10.11), ios(8.0));

    class Texture: public Resource
    {
    public:
        Texture() = delete;

    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
