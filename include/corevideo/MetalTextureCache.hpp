#ifndef METALPP_COREVIDEO_METALTEXTURECACHE_HPP
#define METALPP_COREVIDEO_METALTEXTURECACHE_HPP

#include <system_error>
#include <CoreVideo/CVMetalTextureCache.h>
#include "../corefoundation/Base.hpp"
#include "../foundation/Dictionary.hpp"
#include "../metal/Device.hpp"
#include "../metal/Texture.hpp"
#include "CoreVideoErrorCategory.hpp"

namespace cv
{
    class MetalTextureCache final
    {
        CFTypeRef createTextureCache(CFAllocatorRef allocator, CFDictionaryRef cacheAttributes, id metalDevice, CFDictionaryRef textureAttributes)
        {
            static const auto CVMetalTextureCacheCreateProc = reinterpret_cast<CVReturn(*)(CFAllocatorRef, CFDictionaryRef, id, CFDictionaryRef, CFTypeRef*)>(dlsym(RTLD_DEFAULT, "CVMetalTextureCacheCreate"));

            CFTypeRef metalTextureCache;
            if (const auto result = CVMetalTextureCacheCreateProc(allocator, cacheAttributes, metalDevice, textureAttributes, &metalTextureCache); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to create Metal texture cache"};

            return metalTextureCache;
        }
    public:
        MetalTextureCache(const cf::Allocator& allocator,
                          const ns::Dictionary<ns::Object, ns::Object>& cacheAttributes,
                          const mtl::Device& device,
                          const ns::Dictionary<ns::Object, ns::Object>& textureAttributes):
            ref{createTextureCache(allocator,
                                   reinterpret_cast<CFDictionaryRef>(cacheAttributes.get()),
                                   device,
                                   reinterpret_cast<CFDictionaryRef>(textureAttributes.get()))}
        {
        }

        ~MetalTextureCache()
        {
            if (ref) CFRelease(ref);
        }

        MetalTextureCache(MetalTextureCache&& other) noexcept:
            ref{other.ref}
        {
            other.ref = nullptr;
        }

        MetalTextureCache(const MetalTextureCache& other) noexcept: ref{other.ref}
        {
            if (ref) CFRetain(ref);
        }

        MetalTextureCache& operator=(MetalTextureCache&& other) noexcept
        {
            if (&other == this) return *this;
            if (ref) CFRelease(ref);
            ref = other.ref;
            other.ref = nullptr;
            return *this;
        }

        MetalTextureCache& operator=(const MetalTextureCache& other) noexcept
        {
            if (&other == this) return *this;
            if (other.ref) CFRetain(other.ref);
            if (ref) CFRelease(ref);
            ref = other.ref;
            return *this;
        }

        MetalTextureCache(std::nullptr_t) noexcept {}
        MetalTextureCache(const CFTypeRef r) noexcept: ref{r}
        {
            if (ref) CFRetain(ref);
        }

        MetalTextureCache& operator=(std::nullptr_t) noexcept
        {
            if (ref) CFRelease(ref);
            ref = nullptr;
            return *this;
        }

        [[nodiscard]] operator CFTypeRef() const noexcept
        {
            return ref;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return ref;
        }

        [[nodiscard]] auto retainCount() const noexcept
        {
            return CFGetRetainCount(ref);
        }

    private:
        CFTypeRef ref = nullptr;
    };
}

#endif
