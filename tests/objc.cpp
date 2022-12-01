#include "doctest.h"
#include "objc/Class.hpp"
#include "objc/Object.hpp"

TEST_CASE("Class")
{
    objc::Class<ns::Object> cls{"test"};
    CHECK(cls != ns::Object::cls);
    CHECK(strcmp("test", cls.getName()) == 0);
    CHECK(!cls.isMetaClass());
    CHECK(cls.getVersion() == 0);
    cls.setVersion(1);
    CHECK(cls.getVersion() == 1);
}

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

    const ns::Object obj3;
    CHECK(obj != obj3);
}
