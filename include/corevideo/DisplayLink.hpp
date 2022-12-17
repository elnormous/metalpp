#ifndef METALPP_COREVIDEO_DISPLAYLINK_HPP
#define METALPP_COREVIDEO_DISPLAYLINK_HPP

#include <system_error>
#include <CoreVideo/CVDisplayLink.h>
#include "../coregraphics/DirectDisplay.hpp"
#include "CoreVideoErrorCategory.hpp"

namespace cv
{
    class DisplayLink final
    {
    public:
        explicit DisplayLink(const cg::DirectDisplayID displayId)
        {
            if (const auto result = CVDisplayLinkCreateWithCGDisplay(displayId, &ref); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to create display link"};
        }

        ~DisplayLink()
        {
            CVDisplayLinkRelease(ref);
        }

        DisplayLink(DisplayLink&& other) noexcept:
            ref{other.ref}
        {
            other.ref = nullptr;
        }

        DisplayLink(const DisplayLink& other) noexcept:
            ref{other.ref}
        {
            CVDisplayLinkRetain(ref);
        }

        DisplayLink& operator=(DisplayLink&& other) noexcept
        {
            if (&other == this) return *this;
            CVDisplayLinkRelease(ref);
            ref = other.ref;
            other.ref = nullptr;
            return *this;
        }

        DisplayLink& operator=(const DisplayLink& other) noexcept
        {
            if (&other == this) return *this;
            CVDisplayLinkRetain(other.ref);
            CVDisplayLinkRelease(ref);
            ref = other.ref;
            return *this;
        }

        [[nodiscard]] operator CVDisplayLinkRef() const noexcept
        {
            return ref;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return ref;
        }
        
        [[nodiscard]] auto retainCount() const noexcept
        {
            return ref ? CFGetRetainCount(ref) : 0;
        }
        
        void setCallback(const CVDisplayLinkOutputCallback callback, void* userInfo)
        {
            if (const auto result = CVDisplayLinkSetOutputCallback(ref, callback, userInfo); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to set output callback for the display link"};
        }

        void start()
        {
            if (ref)
                if (const auto result = CVDisplayLinkStart(ref); result != kCVReturnSuccess)
                    throw std::system_error{result, errorCategory, "Failed to start display link"};
        }

        void stop()
        {
            if (ref)
                if (const auto result = CVDisplayLinkStop(ref); result != kCVReturnSuccess)
                    throw std::system_error{result, errorCategory, "Failed to stop display link"};
        }

    private:
        CVDisplayLinkRef ref = nullptr;
    };
}

#endif
