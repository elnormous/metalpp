#ifndef METALPP_COREVIDEO_DISPLAYLINK_HPP
#define METALPP_COREVIDEO_DISPLAYLINK_HPP

#include <dlfcn.h>
#include <CoreVideo/CVDisplayLink.h>
#include "../coregraphics/DirectDisplay.hpp"
#include "CoreVideoErrorCategory.hpp"

namespace cv
{
    inline cg::DirectDisplayID mainDisplayID() noexcept
    {
        static const auto CGMainDisplayIDProc = reinterpret_cast<cg::DirectDisplayID(*)()>(dlsym(RTLD_DEFAULT, "CGMainDisplayID"));
        return CGMainDisplayIDProc();
    }

    class DisplayLink final
    {
    public:
        explicit DisplayLink(const cg::DirectDisplayID displayID)
        {
            if (const auto result = CVDisplayLinkCreateWithCGDisplay(displayID, &ref); result != kCVReturnSuccess)
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

        DisplayLink(const DisplayLink& other) noexcept: ref{CVDisplayLinkRetain(other.ref)} {}

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

        DisplayLink(std::nullptr_t) noexcept {}
        DisplayLink(const CVDisplayLinkRef r) noexcept: ref{CVDisplayLinkRetain(r)} {}

        DisplayLink& operator=(std::nullptr_t) noexcept
        {
            CVDisplayLinkRelease(ref);
            ref = nullptr;
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
            return CFGetRetainCount(ref);
        }

        void setCurrentCGDisplay(CGDirectDisplayID displayID)
        {
            if (const auto result = CVDisplayLinkSetCurrentCGDisplay(ref, displayID); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to set current CG display"};

        }

        void setOutputCallback(const CVDisplayLinkOutputCallback callback, void* userInfo)
        {
            if (const auto result = CVDisplayLinkSetOutputCallback(ref, callback, userInfo); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to set output callback for the display link"};
        }

        void start()
        {
            if (const auto result = CVDisplayLinkStart(ref); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to start display link"};
        }

        void stop()
        {
            if (const auto result = CVDisplayLinkStop(ref); result != kCVReturnSuccess)
                throw std::system_error{result, errorCategory, "Failed to stop display link"};
        }

        auto getNominalOutputVideoRefreshPeriod() const noexcept
        {
            return CVDisplayLinkGetNominalOutputVideoRefreshPeriod(ref);
        }

        auto getActualOutputVideoRefreshPeriod() const noexcept
        {
            return CVDisplayLinkGetActualOutputVideoRefreshPeriod(ref);
        }

        auto isRunning() const noexcept
        {
            return static_cast<bool>(CVDisplayLinkIsRunning(ref));
        }

    private:
        CVDisplayLinkRef ref = nullptr;
    };
}

#endif
