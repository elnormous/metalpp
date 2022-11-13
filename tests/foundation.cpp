#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "metal/Metal.hpp"

TEST_CASE("AutoreleasePool")
{
    ns::AutoreleasePool autoreleasePool;
    mtl::Device device;
    ns::String name = device.name();
    REQUIRE(name.retainCount() == 2);
    autoreleasePool.drain();
    REQUIRE(name.retainCount() == 1);
}

TEST_CASE("Array")
{
    ns::Object obj1;
    ns::Object obj2;
    const ns::Array<ns::Object> arr{obj1, obj2};
    CHECK(arr.retainCount() == 1);
    REQUIRE(arr.count() == 2);

    CHECK(obj1.retainCount() == 2);
    CHECK(obj2.retainCount() == 2);

    ns::Object obj1Copy = arr[0];
    ns::Object obj2Copy = arr.objectAtIndex(1);
    CHECK(obj1 == obj1Copy);
    CHECK(obj2 == obj2Copy);
}

TEST_CASE("Dictionary")
{
    ns::String key1 = "key1";
    ns::Object obj1;
    ns::String key2 = "key2";
    ns::Object obj2;

    const ns::Dictionary<ns::String, ns::Object> dict{obj1, key1, obj2, key2};
    CHECK(dict.retainCount() == 1);
    REQUIRE(dict.count() == 2);
    CHECK(obj1.retainCount() == 2);
    CHECK(obj2.retainCount() == 2);

    ns::Object obj1Copy = dict["key1"];
    ns::Object obj2Copy = dict.objectForKey("key2");
    CHECK(obj1 == obj1Copy);
    CHECK(obj2 == obj2Copy);

    ns::Array<ns::String> keys = dict.allKeys();
    CHECK(keys[0].string() == "key1");
    CHECK(keys[1].string() == "key2");

    ns::Array<ns::Object> values = dict.allValues();
    CHECK(values[0] == obj1);
    CHECK(values[1] == obj2);

    ns::Array<ns::String> keysForObject = dict.allKeysForObject(obj1);
    CHECK(keysForObject[0].string() == "key1");

    const ns::Dictionary<ns::String, ns::Object> dict2{values, keys};
    CHECK(obj1 == dict["key1"]);
    CHECK(obj2 == dict["key2"]);
}

TEST_CASE("String")
{
    const ns::String str = "ab";
    REQUIRE(str.retainCount() > 0);
    REQUIRE(str.length() == 2);
    CHECK(str[0] == 'a');
    CHECK(str[1] == 'b');
    CHECK(str.charAtIndex(0) == 'a');
    CHECK(str.charAtIndex(1) == 'b');
    CHECK(str.string() == "ab");
    CHECK(strcmp(str.cString(), "ab") == 0);
}
