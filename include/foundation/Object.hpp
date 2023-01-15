#ifndef METALPP_FOUNDATION_OBJECT_HPP
#define METALPP_FOUNDATION_OBJECT_HPP

namespace ns
{
    class Copying {};

    template<class Type>
    [[nodiscard]] std::enable_if_t<std::is_base_of_v<Copying, Type>, Type> copy(const Type& object) noexcept
    {
        return Type{objc::sendMessage<id>(object.get(), Object::METALPP_SEL(copy)), adopt};
    }
}

#endif
