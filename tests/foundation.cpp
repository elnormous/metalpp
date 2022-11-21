#include "doctest.h"
#include "foundation/AutoreleasePool.hpp"
#include "foundation/Array.hpp"
#include "foundation/Dictionary.hpp"
#include "foundation/Error.hpp"
#include "foundation/String.hpp"

TEST_CASE("AutoreleasePool")
{
    ns::AutoreleasePool autoreleasePool;
    REQUIRE(autoreleasePool);

    ns::Object obj{};

    using SendMessageProc = id(const void*, SEL);
    SendMessageProc* proc = reinterpret_cast<SendMessageProc*>(&objc_msgSend);
    proc(proc(static_cast<id>(obj), ns::sel::retain), ns::sel::autorelease);
    
    REQUIRE(obj.retainCount() == 2);
    autoreleasePool.drain();
    REQUIRE(obj.retainCount() == 1);
}

TEST_CASE("Array")
{
    ns::AutoreleasePool pool;

    ns::Object obj1;
    ns::Object obj2;
    const ns::Array<ns::Object> arr{obj1, obj2};
    REQUIRE(arr);
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
    ns::AutoreleasePool pool;

    ns::String key1 = "key1";
    ns::Object obj1;
    ns::String key2 = "key2";
    ns::Object obj2;

    const ns::Dictionary<ns::String, ns::Object> dict{obj1, key1, obj2, key2};
    REQUIRE(dict);
    CHECK(dict.retainCount() == 1);
    REQUIRE(dict.count() == 2);
    CHECK(obj1.retainCount() == 2);
    CHECK(obj2.retainCount() == 2);

    ns::Object obj1Copy = dict["key1"];
    ns::Object obj2Copy = dict.objectForKey("key2");
    CHECK(obj1 == obj1Copy);
    CHECK(obj2 == obj2Copy);

    ns::Array<ns::String> keys = dict.allKeys();
    REQUIRE(keys);
    REQUIRE(keys.retainCount() == 2);
    REQUIRE(keys.retainCount() == 2);
    CHECK(keys[0].isEqualToString("key1"));
    CHECK(keys[1].isEqualToString("key2"));

    ns::Array<ns::Object> values = dict.allValues();
    REQUIRE(values);
    REQUIRE(values.retainCount() == 2);
    REQUIRE(values.retainCount() == 2);
    CHECK(values[0] == obj1);
    CHECK(values[1] == obj2);

    ns::Array<ns::String> keysForObject = dict.allKeysForObject(obj1);
    REQUIRE(keysForObject);
    REQUIRE(keysForObject.retainCount() == 2);
    REQUIRE(keysForObject.retainCount() == 2);
    CHECK(keysForObject[0].isEqualToString("key1"));

    const ns::Dictionary<ns::String, ns::Object> dict2{values, keys};
    CHECK(obj1 == dict["key1"]);
    CHECK(obj2 == dict["key2"]);
}

TEST_CASE("Error")
{
    ns::AutoreleasePool pool;

    ns::Error error{"test", 10};
    REQUIRE(error);
    REQUIRE(error.retainCount() == 1);
    CHECK(error.domain().isEqualToString("test"));
    CHECK(error.code() == 10);

    ns::Error errorWithUserInfo{"test2", 11, ns::Dictionary<ns::String, ns::Object>{ns::String{"key"}, ns::String{"value"}}};
    CHECK(errorWithUserInfo.domain().isEqualToString("test2"));
    CHECK(errorWithUserInfo.code() == 11);
    const ns::Dictionary<ns::String, ns::Object> userInfo = errorWithUserInfo.userInfo();
    REQUIRE(userInfo);
    REQUIRE(userInfo.retainCount() > 0);
    CHECK(userInfo.count() == 1);
}

TEST_CASE("String")
{
    ns::AutoreleasePool pool;

    const ns::String str = "ab";
    REQUIRE(str);
    REQUIRE(str.retainCount() > 0);
    REQUIRE(str.length() == 2);
    CHECK(str[0] == 'a');
    CHECK(str[1] == 'b');
    CHECK(str.charAtIndex(0) == 'a');
    CHECK(str.charAtIndex(1) == 'b');
    CHECK(str.string() == "ab");
    CHECK(strcmp(str.cString(), "ab") == 0);
    CHECK(str.isEqualToString("ab"));
    CHECK(!str.isEqualToString("abc"));
}
