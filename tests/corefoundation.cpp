#include "doctest.h"
#include "corefoundation/Base.hpp"

TEST_CASE("Allocator")
{
    cf::Allocator defaultAllocator = cf::Allocator::defaultAllocator();
    REQUIRE(!defaultAllocator);
    CHECK(defaultAllocator == kCFAllocatorDefault);

    cf::Allocator nullptrAllocator = nullptr;
    CHECK(!nullptrAllocator);

    CHECK(defaultAllocator == nullptrAllocator);

    cf::Allocator systemDefaultAllocator = cf::Allocator::systemDefaultAllocator();
    CHECK(systemDefaultAllocator == kCFAllocatorSystemDefault);
    CHECK(systemDefaultAllocator.retainCount());

    cf::Allocator mallocAllocator = cf::Allocator::mallocAllocator();
    CHECK(mallocAllocator == kCFAllocatorMalloc);
    CHECK(mallocAllocator.retainCount());

    cf::Allocator mallocZoneAllocator = cf::Allocator::mallocZoneAllocator();
    CHECK(mallocZoneAllocator == kCFAllocatorMallocZone);
    CHECK(mallocZoneAllocator.retainCount());

    cf::Allocator nullAllocator = cf::Allocator::nullAllocator();
    CHECK(nullAllocator == kCFAllocatorNull);
    CHECK(nullAllocator.retainCount());

    cf::Allocator userContextAllocator = cf::Allocator::userContextAllocator();
    CHECK(userContextAllocator == kCFAllocatorUseContext);

    cf::AllocatorContext context {

    };

    cf::Allocator customAllocator{cf::Allocator::defaultAllocator(), context};
    REQUIRE(customAllocator);
    CHECK(customAllocator.retainCount() == 1);
}
