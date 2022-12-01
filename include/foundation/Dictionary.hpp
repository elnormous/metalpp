#ifndef METALPP_FOUNDATION_DICTIONARY_HPP
#define METALPP_FOUNDATION_DICTIONARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Array.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class KeyType, class ObjectType>
    class Dictionary: public Object
    {
    public:
        static inline const auto cls = objc_lookUpClass("NSDictionary");

        using Object::Object;

        Dictionary() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        Dictionary(const Array<ObjectType>& objects, const Array<KeyType>& keys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithObjects_forKeys_,
                                         objects.get(),
                                         keys.get())}
        {
        }

        template <class ...Args>
        Dictionary(const Args&... objectsAndKeys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithObjectsAndKeys_,
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
            return getRetained<T>(sel::objectForKey_, key.get());
        }

        template<class T = ObjectType>
        [[nodiscard]] auto objectForKey(const KeyType&& key) const noexcept
        {
            return getRetained<T>(sel::objectForKey_, key.get());
        }

        [[nodiscard]] auto allKeys() const noexcept
        {
            return getRetained<Array<KeyType>>(sel::allKeys);
        }

        [[nodiscard]] auto allKeysForObject(const Object& object) const noexcept
        {
            return getRetained<Array<KeyType>>(sel::allKeysForObject_, object.get());
        }

        [[nodiscard]] auto allValues() const noexcept
        {
            return getRetained<Array<ObjectType>>(sel::allValues);
        }

        [[nodiscard]] auto count() const noexcept
        {
            return sendMessage<UInteger>(sel::count);
        }
    };
}

#endif
