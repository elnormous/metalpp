#ifndef METALPP_FOUNDATION_DICTIONARY_HPP
#define METALPP_FOUNDATION_DICTIONARY_HPP

#include "../objc/Object.hpp"
#include "../objc/Selectors.hpp"
#include "Array.hpp"
#include "Classes.hpp"
#include "Selectors.hpp"

namespace ns
{
    template <class KeyType, class ObjectType>
    class Dictionary final: public ns::Object
    {
    public:
        Dictionary() noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::dictionary, ns::sel::alloc), ns::sel::init)}
        {
        }

        Dictionary(const id p) noexcept: Object{p} {}

        Dictionary(const ns::Array<ObjectType>& objects, const ns::Array<KeyType>& keys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::dictionary, ns::sel::alloc), ns::sel::initWithObjects_forKeys_, static_cast<id>(objects), static_cast<id>(keys))}
        {
        }

        template <class ...Args>
        Dictionary(const Args&... objectsAndKeys) noexcept:
            Object{objc::sendMessage<id>(objc::sendMessage<id>(ns::cls::dictionary, ns::sel::alloc), ns::sel::initWithObjectsAndKeys_, static_cast<id>(objectsAndKeys)..., nil)}
        {
        }

        ObjectType operator[](const KeyType& key) const noexcept
        {
            return objectAtIndexedSubscript(key);
        }

        ObjectType objectAtIndexedSubscript(const KeyType& key) const noexcept
        {
            const id object = objc::sendMessage<id>(*this,
                                                    ns::sel::objectForKey_,
                                                    static_cast<id>(key));
            return ObjectType{objc::sendMessage<id>(object, ns::sel::retain)};
        }

        ns::Array<KeyType> allKeys() const noexcept
        {
            const id keys = objc::sendMessage<id>(*this, ns::sel::allKeys);
            return ns::Array<KeyType>{objc::sendMessage<id>(keys, ns::sel::retain)};
        }

        ns::Array<ObjectType> allValues() const noexcept
        {
            const id values = objc::sendMessage<id>(*this, ns::sel::allValues);
            return ns::Array<ObjectType>{objc::sendMessage<id>(values, ns::sel::retain)};
        }

        std::size_t count() const noexcept
        {
            const auto count = objc::sendMessage<NSUInteger>(*this, sel::count);
            return static_cast<std::size_t>(count);
        }
    };
}

#endif
