#ifndef METALPP_FOUNDATION_DICTIONARY_HPP
#define METALPP_FOUNDATION_DICTIONARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Private.hpp"
#include "Array.hpp"

namespace ns
{
    template<class KeyType, class ObjectType>
    class Dictionary: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSDictionary");

        METALPP_PRIVATE_SEL(initWithObjects_forKeys_, "initWithObjects:forKeys:");
        METALPP_PRIVATE_SEL(initWithObjectsAndKeys_, "initWithObjectsAndKeys:");
        METALPP_PRIVATE_SEL(allKeys, "allKeys");
        METALPP_PRIVATE_SEL(allKeysForObject_, "allKeysForObject:");
        METALPP_PRIVATE_SEL(allValues, "allValues");
        METALPP_PRIVATE_SEL(objectForKey_, "objectForKey:");
        METALPP_PRIVATE_SEL(count, "count");
        
        using Object::Object;

        Dictionary() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)), METALPP_SEL(init))}
        {
        }

        Dictionary(const Array<ObjectType>& objects, const Array<KeyType>& keys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithObjects_forKeys_),
                                         objects.get(),
                                         keys.get())}
        {
        }

        template<class ...Args>
        Dictionary(const Args&... objectsAndKeys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, METALPP_SEL(alloc)),
                                         METALPP_SEL(initWithObjectsAndKeys_),
                                         objectsAndKeys.get()...,
                                         nil)}
        {
        }

        [[nodiscard]] auto operator[](const KeyType& key) const noexcept
        {
            return objectForKey<ObjectType>(key);
        }

        [[nodiscard]] auto operator[](const KeyType&& key) const noexcept
        {
            return objectForKey<ObjectType>(std::move(key));
        }

        template<class T = ObjectType>
        [[nodiscard]] auto objectForKey(const KeyType& key) const noexcept
        {
            return getRetained<T>(METALPP_SEL(objectForKey_), key.get());
        }

        template<class T = ObjectType>
        [[nodiscard]] auto objectForKey(const KeyType&& key) const noexcept
        {
            return getRetained<T>(METALPP_SEL(objectForKey_), key.get());
        }

        [[nodiscard]] auto allKeys() const noexcept
        {
            return getRetained<Array<KeyType>>(METALPP_SEL(allKeys));
        }

        [[nodiscard]] auto allKeysForObject(const Object& object) const noexcept
        {
            return getRetained<Array<KeyType>>(METALPP_SEL(allKeysForObject_), object.get());
        }

        [[nodiscard]] auto allValues() const noexcept
        {
            return getRetained<Array<ObjectType>>(METALPP_SEL(allValues));
        }

        [[nodiscard]] auto count() const noexcept
        {
            return sendMessage<UInteger>(METALPP_SEL(count));
        }
    };
}

#endif
