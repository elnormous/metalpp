#ifndef METALPP_METAL_TEXTURE_HPP
#define METALPP_METAL_TEXTURE_HPP

#include <os/availability.h>
#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "../foundation/Object.hpp"
#include "Buffer.hpp"
#include "PixelFormat.hpp"
#include "Resource.hpp"
#include "Types.hpp"

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

    enum class TextureSwizzle: std::uint8_t
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

    class TextureDescriptor final: public ns::Object, public ns::Copying
    {
    public:
        METALPP_PRIVATE_CLS("MTLTextureDescriptor");

        METALPP_PRIVATE_SEL(textureType, "textureType");
        METALPP_PRIVATE_SEL(setTextureType_, "setTextureType:");
        METALPP_PRIVATE_SEL(pixelFormat, "pixelFormat");
        METALPP_PRIVATE_SEL(setPixelFormat_, "setPixelFormat:");
        METALPP_PRIVATE_SEL(width, "width");
        METALPP_PRIVATE_SEL(setWidth_, "setWidth:");
        METALPP_PRIVATE_SEL(height, "height");
        METALPP_PRIVATE_SEL(setHeight_, "setHeight:");
        METALPP_PRIVATE_SEL(depth, "depth");
        METALPP_PRIVATE_SEL(setDepth_, "setDepth:");
        METALPP_PRIVATE_SEL(mipmapLevelCount, "mipmapLevelCount");
        METALPP_PRIVATE_SEL(setMipmapLevelCount_, "setMipmapLevelCount:");
        METALPP_PRIVATE_SEL(sampleCount, "sampleCount");
        METALPP_PRIVATE_SEL(setSampleCount_, "setSampleCount:");
        METALPP_PRIVATE_SEL(arrayLength, "arrayLength");
        METALPP_PRIVATE_SEL(setArrayLength_, "setArrayLength:");
        METALPP_PRIVATE_SEL(cpuCacheMode, "cpuCacheMode");
        METALPP_PRIVATE_SEL(setCpuCacheMode_, "setCpuCacheMode:");
        METALPP_PRIVATE_SEL(storageMode, "storageMode");
        METALPP_PRIVATE_SEL(setStorageMode_, "setStorageMode:");
        METALPP_PRIVATE_SEL(hazardTrackingMode, "hazardTrackingMode");
        METALPP_PRIVATE_SEL(setHazardTrackingMode_, "setHazardTrackingMode:");
        METALPP_PRIVATE_SEL(resourceOptions, "resourceOptions");
        METALPP_PRIVATE_SEL(usage, "usage");
        METALPP_PRIVATE_SEL(setUsage_, "setUsage:");
        METALPP_PRIVATE_SEL(allowGPUOptimizedContents, "allowGPUOptimizedContents");
        METALPP_PRIVATE_SEL(setAllowGPUOptimizedContents_, "setAllowGPUOptimizedContents:");
        METALPP_PRIVATE_SEL(compressionType, "compressionType");
        METALPP_PRIVATE_SEL(setCompressionType_, "setCompressionType:");
        METALPP_PRIVATE_SEL(swizzle, "swizzle");
        METALPP_PRIVATE_SEL(setSwizzle_, "setSwizzle:");

        TextureDescriptor() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init)), ns::adopt}
        {
        }

        [[nodiscard]] auto textureType() const noexcept
        {
            return sendMessage<TextureType>(METALPP_SEL(textureType));
        }

        void setTextureType(const TextureType textureType) noexcept
        {
            sendMessage(METALPP_SEL(setTextureType_), textureType);
        }

        [[nodiscard]] auto pixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(METALPP_SEL(pixelFormat));
        }

        void setPixelFormat(const PixelFormat pixelFormat) noexcept
        {
            sendMessage(METALPP_SEL(setPixelFormat_), pixelFormat);
        }

        [[nodiscard]] auto width() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(width));
        }

        void setWidth(const ns::UInteger width) noexcept
        {
            sendMessage(METALPP_SEL(setWidth_), width);
        }

        [[nodiscard]] auto height() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(height));
        }

        void setHeight(const ns::UInteger height) noexcept
        {
            sendMessage(METALPP_SEL(setHeight_), height);
        }

        [[nodiscard]] auto depth() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(depth));
        }

        void setDepth(const ns::UInteger depth) noexcept
        {
            sendMessage(METALPP_SEL(setDepth_), depth);
        }

        [[nodiscard]] auto mipmapLevelCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(mipmapLevelCount));
        }

        void setMipmapLevelCount(const ns::UInteger mipmapLevelCount) noexcept
        {
            sendMessage(METALPP_SEL(setMipmapLevelCount_), mipmapLevelCount);
        }

        [[nodiscard]] auto sampleCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(sampleCount));
        }

        void setSampleCount(const ns::UInteger sampleCount) noexcept
        {
            sendMessage(METALPP_SEL(setSampleCount_), sampleCount);
        }

        [[nodiscard]] auto arrayLength() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(arrayLength));
        }

        void setArrayLength(const ns::UInteger arrayLength) noexcept
        {
            sendMessage(METALPP_SEL(setArrayLength_), arrayLength);
        }

        [[nodiscard]] auto cpuCacheMode() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<CPUCacheMode>(METALPP_SEL(cpuCacheMode));
        }

        void setCpuCacheMode(const CPUCacheMode cpuCacheMode) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(METALPP_SEL(setCpuCacheMode_), cpuCacheMode);
        }

        [[nodiscard]] auto storageMode() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<StorageMode>(METALPP_SEL(storageMode));
        }

        void setStorageMode(const StorageMode storageMode) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(METALPP_SEL(setStorageMode_), storageMode);
        }

        [[nodiscard]] auto hazardTrackingMode() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<HazardTrackingMode>(METALPP_SEL(hazardTrackingMode));
        }

        void setHazardTrackingMode(const HazardTrackingMode hazardTrackingMode) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(setHazardTrackingMode_), hazardTrackingMode);
        }

        [[nodiscard]] auto usage() const noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            return sendMessage<TextureUsage>(METALPP_SEL(usage));
        }

        void setUsage(const TextureUsage usage) noexcept API_AVAILABLE(macos(10.11), ios(9.0))
        {
            sendMessage(METALPP_SEL(setUsage_), usage);
        }

        [[nodiscard]] auto allowGPUOptimizedContents() const noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            return sendMessage<BOOL>(METALPP_SEL(allowGPUOptimizedContents)) == YES;
        }

        void setAllowGPUOptimizedContents(const bool allowGPUOptimizedContents) noexcept API_AVAILABLE(macos(10.14), ios(12.0))
        {
            sendMessage(METALPP_SEL(setAllowGPUOptimizedContents_), allowGPUOptimizedContents ? YES : NO);
        }

        [[nodiscard]] auto compressionType() const noexcept API_AVAILABLE(macos(12.5), ios(15.0))
        {
            return sendMessage<TextureCompressionType>(METALPP_SEL(compressionType));
        }

        void setCompressionType(const TextureCompressionType compressionType) noexcept API_AVAILABLE(macos(12.5), ios(15.0))
        {
            sendMessage(METALPP_SEL(setCompressionType_), compressionType);
        }

        [[nodiscard]] auto swizzle() const noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            return sendMessage<TextureSwizzleChannels>(METALPP_SEL(swizzle));
        }

        void setSwizzle(const TextureSwizzleChannels& swizzle) noexcept API_AVAILABLE(macos(10.15), ios(13.0))
        {
            sendMessage(METALPP_SEL(setSwizzle_), swizzle);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    class Texture final: public Resource
    {
    public:
        METALPP_PRIVATE_SEL(textureType, "textureType");
        METALPP_PRIVATE_SEL(pixelFormat, "pixelFormat");
        METALPP_PRIVATE_SEL(width, "width");
        METALPP_PRIVATE_SEL(height, "height");
        METALPP_PRIVATE_SEL(depth, "depth");
        METALPP_PRIVATE_SEL(mipmapLevelCount, "mipmapLevelCount");
        METALPP_PRIVATE_SEL(sampleCount, "sampleCount");
        METALPP_PRIVATE_SEL(arrayLength, "arrayLength");
        METALPP_PRIVATE_SEL(usage, "usage");
        METALPP_PRIVATE_SEL(compressionType, "compressionType");
        METALPP_PRIVATE_SEL(gpuResourceID, "gpuResourceID");
        METALPP_PRIVATE_SEL(replaceRegion_mipmapLevel_withBytes_bytesPerRow_, "replaceRegion:mipmapLevel:withBytes:bytesPerRow:");

        using Resource::Resource;
        using Resource::operator=;

        Texture() = delete;

        [[nodiscard]] auto textureType() const noexcept
        {
            return sendMessage<TextureType>(METALPP_SEL(textureType));
        }

        [[nodiscard]] auto pixelFormat() const noexcept
        {
            return sendMessage<PixelFormat>(METALPP_SEL(pixelFormat));
        }

        [[nodiscard]] auto width() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(width));
        }

        [[nodiscard]] auto height() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(height));
        }

        [[nodiscard]] auto depth() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(depth));
        }

        [[nodiscard]] auto mipmapLevelCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(mipmapLevelCount));
        }

        [[nodiscard]] auto sampleCount() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(sampleCount));
        }

        [[nodiscard]] auto arrayLength() const noexcept
        {
            return sendMessage<ns::UInteger>(METALPP_SEL(arrayLength));
        }

        [[nodiscard]] auto usage() const noexcept
        {
            return sendMessage<TextureUsage>(METALPP_SEL(usage));
        }

        [[nodiscard]] auto compressionType() const noexcept API_AVAILABLE(macos(12.5), ios(15.0))
        {
            return sendMessage<TextureCompressionType>(METALPP_SEL(compressionType));
        }

        [[nodiscard]] auto gpuResourceID() const noexcept API_AVAILABLE(macos(13.0), ios(16.0))
        {
            return sendMessage<ResourceID>(METALPP_SEL(gpuResourceID));
        }

        void replaceRegion(const Region& region,
                           const ns::UInteger level,
                           const void* pixelBytes,
                           const ns::UInteger bytesPerRow) noexcept
        {

            return sendMessage(METALPP_SEL(replaceRegion_mipmapLevel_withBytes_bytesPerRow_), region, level, pixelBytes, bytesPerRow);
        }
    } API_AVAILABLE(macos(10.11), ios(8.0));

    inline Texture Buffer::newTexture(const TextureDescriptor& descriptor, const ns::UInteger offset, const ns::UInteger bytesPerRow) API_AVAILABLE(macos(10.13), ios(8.0))
    {
        return Texture{sendMessage<id>(METALPP_SEL(newTextureWithDescriptor_offset_bytesPerRow_),
                                       descriptor.get(),
                                       offset,
                                       bytesPerRow)};
    }
}

#endif
