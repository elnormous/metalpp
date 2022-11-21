#ifndef METALPP_METAL_TEXTURE_HPP
#define METALPP_METAL_TEXTURE_HPP

#include <os/availability.h>
#include "PixelFormat.hpp"
#include "Resource.hpp"
#include "Selectors.hpp"

namespace mtl
{
    enum class TextureType: NSUInteger
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

    enum class TextureUsage: NSUInteger
    {
        Unknown         = 0x0000,
        ShaderRead      = 0x0001,
        ShaderWrite     = 0x0002,
        RenderTarget    = 0x0004,
        PixelFormatView = 0x0010,
    } API_AVAILABLE(macos(10.11), ios(9.0));

    enum class TextureCompressionType: NSInteger
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

        [[nodiscard]] NSUInteger width() const noexcept
        {
            return sendMessage<NSUInteger>(sel::width);
        }

        void setWidth(NSUInteger width) noexcept
        {
            sendMessage(sel::setWidth_, width);
        }

        [[nodiscard]] NSUInteger height() const noexcept
        {
            return sendMessage<NSUInteger>(sel::height);
        }

        void setHeight(NSUInteger height) noexcept
        {
            sendMessage(sel::setHeight_, height);
        }

        [[nodiscard]] NSUInteger depth() const noexcept
        {
            return sendMessage<NSUInteger>(sel::depth);
        }

        void setDepth(NSUInteger depth) noexcept
        {
            sendMessage(sel::setDepth_, depth);
        }

        [[nodiscard]] NSUInteger mipmapLevelCount() const noexcept
        {
            return sendMessage<NSUInteger>(sel::mipmapLevelCount);
        }

        void setMipmapLevelCount(NSUInteger mipmapLevelCount) noexcept
        {
            sendMessage(sel::setMipmapLevelCount_, mipmapLevelCount);
        }

        [[nodiscard]] NSUInteger sampleCount() const noexcept
        {
            return sendMessage<NSUInteger>(sel::sampleCount);
        }

        void setSampleCount(NSUInteger sampleCount) noexcept
        {
            sendMessage(sel::setSampleCount_, sampleCount);
        }

        [[nodiscard]] NSUInteger arrayLength() const noexcept
        {
            return sendMessage<NSUInteger>(sel::arrayLength);
        }

        void setArrayLength(NSUInteger arrayLength) noexcept
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

        [[nodiscard]] NSUInteger width() const noexcept
        {
            return sendMessage<NSUInteger>(sel::width);
        }

        [[nodiscard]] NSUInteger height() const noexcept
        {
            return sendMessage<NSUInteger>(sel::height);
        }

        [[nodiscard]] NSUInteger depth() const noexcept
        {
            return sendMessage<NSUInteger>(sel::depth);
        }

        [[nodiscard]] NSUInteger mipmapLevelCount() const noexcept
        {
            return sendMessage<NSUInteger>(sel::mipmapLevelCount);
        }

        [[nodiscard]] NSUInteger sampleCount() const noexcept
        {
            return sendMessage<NSUInteger>(sel::sampleCount);
        }

        [[nodiscard]] NSUInteger arrayLength() const noexcept
        {
            return sendMessage<NSUInteger>(sel::arrayLength);
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
