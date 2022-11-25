#ifndef METALPP_COREVIDEO_COREVIDEOERRORCATEGORY_HPP
#define METALPP_COREVIDEO_COREVIDEOERRORCATEGORY_HPP

#include <system_error>
#include <CoreVideo/CVReturn.h>

namespace cv
{
    class ErrorCategory final: public std::error_category
    {
    public:
        const char* name() const noexcept override
        {
            return "CoreVideo";
        }

        std::string message(const int condition) const override
        {
            switch (condition)
            {
                case kCVReturnError: return "kCVReturnError";
                case kCVReturnInvalidArgument: return "kCVReturnInvalidArgument";
                case kCVReturnAllocationFailed: return "kCVReturnAllocationFailed";
                case kCVReturnUnsupported: return "kCVReturnUnsupported";

                    // DisplayLink related errors
                case kCVReturnInvalidDisplay: return "kCVReturnInvalidDisplay";
                case kCVReturnDisplayLinkAlreadyRunning: return "kCVReturnDisplayLinkAlreadyRunning";
                case kCVReturnDisplayLinkNotRunning: return "kCVReturnDisplayLinkNotRunning";
                case kCVReturnDisplayLinkCallbacksNotSet: return "kCVReturnDisplayLinkCallbacksNotSet";

                    // Buffer related errors
                case kCVReturnInvalidPixelFormat: return "kCVReturnInvalidPixelFormat";
                case kCVReturnInvalidSize: return "kCVReturnInvalidSize";
                case kCVReturnInvalidPixelBufferAttributes: return "kCVReturnInvalidPixelBufferAttributes";
                case kCVReturnPixelBufferNotOpenGLCompatible: return "kCVReturnPixelBufferNotOpenGLCompatible";
                case kCVReturnPixelBufferNotMetalCompatible: return "kCVReturnPixelBufferNotMetalCompatible";

                    // Buffer Pool related errors
                case kCVReturnWouldExceedAllocationThreshold: return "kCVReturnWouldExceedAllocationThreshold";
                case kCVReturnPoolAllocationFailed: return "kCVReturnPoolAllocationFailed";
                case kCVReturnInvalidPoolAttributes: return "kCVReturnInvalidPoolAttributes";
                case kCVReturnRetry: return "kCVReturnRetry";
                default: return "Unknown error (" + std::to_string(condition) + ")";
            }
        }
    };

    inline const ErrorCategory errorCategory;
}

#endif
