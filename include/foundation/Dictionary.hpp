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
        static inline const auto cls = objc_lookUpClass("NSDictionary");
    public:
        Dictionary() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        Dictionary(const id p) noexcept: Object{p} {}

        Dictionary(const Array<ObjectType>& objects, const Array<KeyType>& keys) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, sel::alloc),
                                   sel::initWithObjects_forKeys_,
                                   static_cast<id>(objects),
                                   static_cast<id>(keys))}
        {
        }

        template <class ...Args>
        Dictionary(const Args&... objectsAndKeys) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, sel::alloc),
                                   sel::initWithObjectsAndKeys_,
                                   static_cast<id>(objectsAndKeys)...,
                                   nil)}
        {
        }

        [[nodiscard]] ObjectType operator[](const KeyType& key) const noexcept
        {
            return objectForKey(key);
        }

        [[nodiscard]] ObjectType operator[](KeyType&& key) const noexcept
        {
            return objectForKey(std::move(key));
        }

        [[nodiscard]] ObjectType objectForKey(const KeyType& key) const noexcept
        {
            return getRetained<ObjectType>(sel::objectForKey_, static_cast<id>(key));
        }

        [[nodiscard]] Array<KeyType> allKeys() const noexcept
        {
            return getRetained<Array<KeyType>>(sel::allKeys);
        }

        [[nodiscard]] Array<KeyType> allKeysForObject(const Object& object) const noexcept
        {
            return getRetained<Array<KeyType>>(sel::allKeysForObject_, static_cast<id>(object));
        }

        [[nodiscard]] Array<ObjectType> allValues() const noexcept
        {
            return getRetained<Array<ObjectType>>(sel::allValues);
        }

        [[nodiscard]] UInteger count() const noexcept
        {
            return sendMessage<UInteger>(sel::count);
        }
    };
}

#endif
