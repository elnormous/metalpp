#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "metal/Metal.hpp"

TEST_CASE("NSObject")
{
    const ns::Object object;
    CHECK(object.retainCount() == 1);

    const ns::Object object2 = object;
    CHECK(object.retainCount() == 2);
}
