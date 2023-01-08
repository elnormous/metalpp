#include "doctest.h"
#include <thread>
#include "dispatch/Data.hpp"
#include "dispatch/Semaphore.hpp"

TEST_CASE("Data")
{
    char buffer[] = {'a', 'b', 'c'};
    dispatch::Data data{buffer, sizeof(buffer), nullptr, DISPATCH_DATA_DESTRUCTOR_DEFAULT};
    REQUIRE(data);
    CHECK(data.getSize() == sizeof(buffer));
}

TEST_CASE("Semaphore")
{
    dispatch::Semaphore sempahore{2};
    REQUIRE(sempahore);

    sempahore.wait(DISPATCH_TIME_FOREVER);
    sempahore.wait(DISPATCH_TIME_FOREVER);

    std::thread t{[&sempahore]() {
        sempahore.signal();
        sempahore.signal();
        sempahore.signal();
    }};

    sempahore.wait(DISPATCH_TIME_FOREVER);

    t.join();
}
