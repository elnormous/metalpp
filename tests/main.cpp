#define DOCTEST_CONFIG_USE_STD_HEADERS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "objc/Object.hpp"

TEST_CASE("Object")
{
    const ns::Object obj;
    REQUIRE(obj);
    CHECK(obj.retainCount() == 1);

    {
        const ns::Object obj2 = obj;
        CHECK(obj.retainCount() == 2);
        CHECK(obj == obj2);
    }

    CHECK(obj.retainCount() == 1);
}
