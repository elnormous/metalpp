#include "doctest.h"
#include "corefoundation/Base.hpp"

TEST_CASE("Allocator")
{
    cf::Allocator defaultAllocator = kCFAllocatorDefault;
    REQUIRE(!defaultAllocator);

    cf::Allocator nullAllocator = nullptr;
    REQUIRE(!nullAllocator);

    CHECK(defaultAllocator == nullAllocator);
}
