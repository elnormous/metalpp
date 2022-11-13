#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "metal/Metal.hpp"

TEST_CASE("NSObject")
{
    const ns::Object obj;
    CHECK(obj.retainCount() == 1);

    {
        const ns::Object obj2 = obj;
        CHECK(obj.retainCount() == 2);
        CHECK(obj == obj2);
    }

    CHECK(obj.retainCount() == 1);
}

TEST_CASE("NSArray")
{
    ns::Object obj1;
    ns::Object obj2;
    const ns::Array<ns::Object> arr{obj1, obj2};
    CHECK(arr.retainCount() == 1);
    CHECK(arr.count() == 2);

    CHECK(obj1.retainCount() == 2);
    CHECK(obj2.retainCount() == 2);

    ns::Object obj1Copy = arr[0];
    ns::Object obj2Copy = arr.objectAtIndex(1);
    CHECK(obj1 == obj1Copy);
    CHECK(obj2 == obj2Copy);
}

TEST_CASE("NSDictionary")
{
    ns::String key1 = "key1";
    ns::Object obj1;
    ns::String key2 = "key2";
    ns::Object obj2;
    const ns::Dictionary<ns::String, ns::Object> dict{obj1, key1, obj2, key2};
    CHECK(dict.retainCount() == 1);
    CHECK(dict.count() == 2);
    CHECK(obj1.retainCount() == 2);
    CHECK(obj2.retainCount() == 2);

    ns::Object obj1Copy = dict["key1"];
    ns::Object obj2Copy = dict.objectForKey("key2");
    CHECK(obj1 == obj1Copy);
    CHECK(obj2 == obj2Copy);
}

TEST_CASE("NSString")
{
    const ns::String str = "ab";
    CHECK(str.length() == 2);
    CHECK(str[0] == 'a');
    CHECK(str[1] == 'b');
    CHECK(str.charAtIndex(0) == 'a');
    CHECK(str.charAtIndex(1) == 'b');
    CHECK(str.string() == "ab");
    CHECK(strcmp(str.cString(), "ab") == 0);
}
