#include <condition_variable>
#include <mutex>
#include "doctest.h"
#include "corevideo/DisplayLink.hpp"

namespace
{
    struct Flag final
    {
        bool flag = false;
        std::mutex mutex;
        std::condition_variable condition;
    };

    CVReturn callback(CVDisplayLinkRef,
                      const CVTimeStamp*,
                      const CVTimeStamp*,
                      CVOptionFlags,
                      CVOptionFlags*,
                      void* displayLinkContext)
    {
        Flag& flag = *static_cast<Flag*>(displayLinkContext);

        std::unique_lock lock{flag.mutex};
        flag.flag = true;
        lock.unlock();
        flag.condition.notify_all();

        return kCVReturnSuccess;
    }
}

TEST_CASE("DisplayLink")
{
    const auto mainDisplayId = cv::mainDisplayID();
    REQUIRE(mainDisplayId);

    cv::DisplayLink displayLink{mainDisplayId};
    REQUIRE(displayLink);
    CHECK(displayLink.retainCount());

    Flag flag;
    displayLink.setOutputCallback(callback, &flag);
    displayLink.start();

    CHECK(displayLink.isRunning());

    displayLink.setCurrentCGDisplay(mainDisplayId);

    std::unique_lock lock{flag.mutex};
    while (!flag.flag) flag.condition.wait(lock);

    displayLink.stop();
}
