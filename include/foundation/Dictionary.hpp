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
        using Object::Object;

        Dictionary() noexcept:
            Object{sendMessage<id>(sendMessage<id>(cls, sel::alloc), sel::init)}
        {
        }

        Dictionary(const Array<ObjectType>& objects, const Array<KeyType>& keys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithObjects_forKeys_,
                                         static_cast<id>(objects),
                                         static_cast<id>(keys))}
        {
        }

        template <class ...Args>
        Dictionary(const Args&... objectsAndKeys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(cls, sel::alloc),
                                         sel::initWithObjectsAndKeys_,
                                         static_cast<id>(objectsAndKeys)...,
                                         nil)}
        {
        }

        [[nodiscard]] auto operator[](const KeyType& key) const noexcept
        {
            return objectForKey(key);
        }

        [[nodiscard]] auto operator[](KeyType&& key) const noexcept
        {
            return objectForKey(std::move(key));
        }

        [[nodiscard]] auto objectForKey(const KeyType& key) const noexcept
        {
            return getRetained<ObjectType>(sel::objectForKey_, static_cast<id>(key));
        }

        [[nodiscard]] auto allKeys() const noexcept
        {
            return getRetained<Array<KeyType>>(sel::allKeys);
        }

        [[nodiscard]] auto allKeysForObject(const Object& object) const noexcept
        {
            return getRetained<Array<KeyType>>(sel::allKeysForObject_, static_cast<id>(object));
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
