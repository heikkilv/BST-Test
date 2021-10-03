#include "bstnode_base.hh"
#include <string>
#include "bstnode_utils.hh"


template<typename Key, typename Value>
BSTNodeBase<Key, Value>::BSTNodeBase() :
    key_{},
    value_{}
{}

template<typename Key, typename Value>
BSTNodeBase<Key, Value>::BSTNodeBase(
    const key_type& key,
    const value_type& value
) :
    key_{key},
    value_{value}
{}

template<typename Key, typename Value>
typename BSTNodeBase<Key, Value>::key_type BSTNodeBase<Key, Value>::getKey() const
{
    return key_;
}

template<typename Key, typename Value>
typename BSTNodeBase<Key, Value>::value_type BSTNodeBase<Key, Value>::getValue() const
{
    return value_;
}

template<typename Key, typename Value>
BSTNodeBase<Key, Value>::operator std::string() const
{
    return getValueString(this);
}

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BSTNodeBase<Key, Value>& node)
{
    os << static_cast<std::string>(node);
    return os;
}
