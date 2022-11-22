#ifndef METALPP_METAL_TEXTURE_HPP
#define METALPP_METAL_TEXTURE_HPP

#include <os/availability.h>
#include "PixelFormat.hpp"
#include "Resource.hpp"
#include "Selectors.hpp"

namespace mtl
{
    enum class TextureType: ns::UInteger
    {
        Type1D = 0,
        Type1DArray = 1,
        Type2D = 2,
        Type2DArray = 3,
        Type2DMultisample = 4,
        TypeCube = 5,
        TypeCubeArray API_AVAILABLE(macos(10.11), ios(11.0)) = 6,
        Type3D = 7,
        Type2DMultisampleArray API_AVAILABLE(macos(10.14), ios(14.0)) = 8,
        TypeTextureBuffer API_AVAILABLE(macos(10.14), ios(12.0)) = 9
    } API_AVAILABLE(macos(10.11), ios(8.0));

    enum class TextureSwizzle: uint8_t
    {
        Zero = 0,
        One = 1,
        Red = 2,
        Green = 3,
        Blue = 4,
        Alpha = 5,
    } API_AVAILABLE(macos(10.15), ios(13.0));

    struct TextureSwizzleChannels final
    {
        TextureSwizzle red;
        TextureSwizzle green;
        TextureSwizzle blue;
        TextureSwizzle alpha;
    } API_AVAILABLE(macos(10.15), ios(13.0));

    enum class TextureUsage: ns::UInteger
    {
        Unknown         = 0x0000,
        ShaderRead      = 0x0001,
        ShaderWrite     = 0x0002,
        RenderTarget    = 0x0004,
        PixelFormatView = 0x0010,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class TextureCompressionType: ns::Integer
    {
        Lossless = 0,
        Lossy = 1,
    } API_AVAILABLE(macos(12.5), ios(15.0));

    class TextureDescriptor final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("MTLTextureDescriptor");
    public:
        TextureDescriptor():
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        [[nodiscard]] TextureType textureType() const noexcept
        {
            return sendMessage<TextureType>(sel::textureType);
        }

        void setTextureType(TextureType textureType) noexcept
        {
            sendMessage(sel::setTextureType_, textureType);
        }

        [[nodiscard]] PixelFormat pixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(sel::pixelFormat);
        }

        void setPixelFormat(PixelFormat pixelFormat) noexcept
        {
            sendMessage(sel::setPixelFormat_, pixelFormat);
        }

        [[nodiscard]] ns::UInteger width() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::width);
        }

        void setWidth(ns::UInteger width) noexcept
        {
            sendMessage(sel::setWidth_, width);
        }

        [[nodiscard]] ns::UInteger height() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::height);
        }

        void setHeight(ns::UInteger height) noexcept
        {
            sendMessage(sel::setHeight_, height);
        }

        [[nodiscard]] ns::UInteger depth() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::depth);
        }

        void setDepth(ns::UInteger depth) noexcept
        {
            sendMessage(sel::setDepth_, depth);
        }

        [[nodiscard]] ns::UInteger mipmapLevelCount() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::mipmapLevelCount);
        }

        void setMipmapLevelCount(ns::UInteger mipmapLevelCount) noexcept
        {
            sendMessage(sel::setMipmapLevelCount_, mipmapLevelCount);
        }

        [[nodiscard]] ns::UInteger sampleCount() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::sampleCount);
        }

        void setSampleCount(ns::UInteger sampleCount) noexcept
        {
            sendMessage(sel::setSampleCount_, sampleCount);
        }

        [[nodiscard]] ns::UInteger arrayLength() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::arrayLength);
        }

        void setArrayLength(ns::UInteger arrayLength) noexcept
        {
            sendMessage(sel::setArrayLength_, arrayLength);
        }

        [[nodiscard]] CPUCacheMode cpuCacheMode() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<CPUCacheMode>(sel::cpuCacheMode);
        }

        void setCpuCacheMode(CPUCacheMode cpuCacheMode) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(sel::setCpuCacheMode_, cpuCacheMode);
        }

        [[nodiscard]] StorageMode storageMode() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<StorageMode>(sel::storageMode);
        }

        void setStorageMode(StorageMode storageMode) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(sel::setStorageMode_, storageMode);
        }

        [[nodiscard]] HazardTrackingMode hazardTrackingMode() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HazardTrackingMode>(sel::hazardTrackingMode);
        }

        void setHazardTrackingMode(HazardTrackingMode hazardTrackingMode) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(sel::setHazardTrackingMode_, hazardTrackingMode);
        }

        [[nodiscard]] TextureUsage usage() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<TextureUsage>(sel::usage);
        }

        void setUsage(TextureUsage usage) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(sel::setUsage_, usage);
        }

        [[nodiscard]] bool allowGPUOptimizedContents() const noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            return sendMessage<BOOL>(sel::allowGPUOptimizedContents) == YES;
        }

        void setAllowGPUOptimizedContents(bool allowGPUOptimizedContents) noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            sendMessage(sel::setAllowGPUOptimizedContents_, allowGPUOptimizedContents ? YES : NO);
        }

        [[nodiscard]] TextureCompressionType compressionType() const noexcept API_AVAILABLE(macos(12.5), ios(15.0))
        {
            return sendMessage<TextureCompressionType>(sel::compressionType);
        }

        void setCompressionType(TextureCompressionType compressionType) noexcept API_AVAILABLE(macos(12.5), ios(15.0))
        {
            sendMessage(sel::setCompressionType_, compressionType);
        }

        [[nodiscard]] TextureSwizzleChannels swizzle() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<TextureSwizzleChannels>(sel::swizzle);
        }

        void setSwizzle(const TextureSwizzleChannels& swizzle) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(sel::setSwizzle_, swizzle);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class Texture final: public Resource
    {
    public:
        Texture() = delete;

        [[nodiscard]] TextureType textureType() const noexcept
        {
            return sendMessage<TextureType>(sel::textureType);
        }

        [[nodiscard]] PixelFormat pixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(sel::pixelFormat);
        }

        [[nodiscard]] ns::UInteger width() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::width);
        }

        [[nodiscard]] ns::UInteger height() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::height);
        }

        [[nodiscard]] ns::UInteger depth() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::depth);
        }

        [[nodiscard]] ns::UInteger mipmapLevelCount() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::mipmapLevelCount);
        }

        [[nodiscard]] ns::UInteger sampleCount() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::sampleCount);
        }

        [[nodiscard]] ns::UInteger arrayLength() const noexcept
        {
            return sendMessage<ns::UInteger>(sel::arrayLength);
        }

        [[nodiscard]] TextureUsage usage() const noexcept
        {
            return sendMessage<TextureUsage>(sel::usage);
        }

        [[nodiscard]] TextureCompressionType compressionType() const noexcept API_AVAILABLE(macos(12.5), ios(15.0))
        {
            return sendMessage<TextureCompressionType>(sel::compressionType);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));
}

#endif
