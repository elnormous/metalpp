#include "doctest.h"
#include "corefoundation/Base.hpp"
#include "corefoundation/Dictionary.hpp"

TEST_CASE("Allocator")
{
    cf::Allocator defaultAllocator = cf::Allocator::defaultAllocator();
    REQUIRE(!defaultAllocator);
    CHECK(defaultAllocator == kCFAllocatorDefault);

    std::uint8_t data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    void* memory = defaultAllocator.allocate(sizeof(data), 0);
    std::memcpy(memory, data, sizeof(data));

    memory = defaultAllocator.reallocate(memory, sizeof(data), 0);
    CHECK(std::memcmp(memory, data, sizeof(data)) == 0);

    defaultAllocator.deallocate(memory);

    CHECK(defaultAllocator.getPreferredSizeForSize(8, 0));

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

TEST_CASE("Dictionary")
{
    cf::Dictionary emptyDictionary{cf::Allocator::defaultAllocator(), nullptr, nullptr, 0};
    REQUIRE(emptyDictionary);
}
