#include "doctest.h"
#include "corefoundation/Base.hpp"

TEST_CASE("Allocator")
{
    cf::Allocator defaultAllocator = cf::Allocator::defaultAllocator();
    REQUIRE(!defaultAllocator);
    CHECK(defaultAllocator == kCFAllocatorDefault);

    cf::Allocator nullptrAllocator = nullptr;
    REQUIRE(!nullptrAllocator);

    CHECK(defaultAllocator == nullptrAllocator);

    cf::Allocator systemDefaultAllocator = cf::Allocator::systemDefaultAllocator();
    CHECK(systemDefaultAllocator == kCFAllocatorSystemDefault);

    cf::Allocator mallocAllocator = cf::Allocator::mallocAllocator();
    CHECK(mallocAllocator == kCFAllocatorMalloc);

    cf::Allocator mallocZoneAllocator = cf::Allocator::mallocZoneAllocator();
    CHECK(mallocZoneAllocator == kCFAllocatorMallocZone);

    cf::Allocator nullAllocator = cf::Allocator::nullAllocator();
    CHECK(nullAllocator == kCFAllocatorNull);

    cf::Allocator userContextAllocator = cf::Allocator::userContextAllocator();
    CHECK(userContextAllocator == kCFAllocatorUseContext);
}
