#ifndef METALPP_FOUNDATION_DICTIONARY_HPP
#define METALPP_FOUNDATION_DICTIONARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Array.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class KeyType, class ObjectType>
    class Dictionary final: public ns::Object
    {
        static inline const auto cls = objc_lookUpClass("NSDictionary");
    public:
        Dictionary() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc), ns::sel::init)}
        {
        }

        Dictionary(const id p) noexcept: Object{p} {}

        Dictionary(const ns::Array<ObjectType>& objects, const ns::Array<KeyType>& keys) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc),
                                   ns::sel::initWithObjects_forKeys_,
                                   static_cast<id>(objects),
                                   static_cast<id>(keys))}
        {
        }

        template <class ...Args>
        Dictionary(const Args&... objectsAndKeys) noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, ns::sel::alloc),
                                   ns::sel::initWithObjectsAndKeys_,
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
            const id object = sendMessage<id>(ns::sel::objectForKey_,
                                              static_cast<id>(key));
            return ObjectType{sendMessage<id>(object, ns::sel::retain)};
        }

        [[nodiscard]] ns::Array<KeyType> allKeys() const noexcept
        {
            const id keys = sendMessage<id>(ns::sel::allKeys);
            return ns::Array<KeyType>{sendMessage<id>(keys, ns::sel::retain)};
        }

        [[nodiscard]] ns::Array<KeyType> allKeysForObject(const ns::Object& object) const noexcept
        {
            const id keys = sendMessage<id>(ns::sel::allKeysForObject_, static_cast<id>(object));
            return ns::Array<KeyType>{sendMessage<id>(keys, ns::sel::retain)};
        }

        [[nodiscard]] ns::Array<ObjectType> allValues() const noexcept
        {
            const id values = sendMessage<id>(ns::sel::allValues);
            return ns::Array<ObjectType>{sendMessage<id>(values, ns::sel::retain)};
        }

        [[nodiscard]] NSUInteger count() const noexcept
        {
            return sendMessage<NSUInteger>(sel::count);
        }
    };
}

#endif
