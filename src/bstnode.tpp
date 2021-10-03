#include "bstnode.hh"
#include <string>
#include "bstnode_utils.hh"


template<typename Key, typename Value>
BSTNode<Key, Value>::BSTNode() :
    BSTNodeBase<Key, Value>(),
    parent_{nullptr},
    left_{nullptr},
    right_{nullptr}
{}

template<typename Key, typename Value>
BSTNode<Key, Value>::BSTNode(
    const key_type& key,
    const value_type& value
) :
    BSTNodeBase<Key, Value>(key, value),
    parent_{nullptr},
    left_{nullptr},
    right_{nullptr}
{}

template<typename Key, typename Value>
BSTNode<Key, Value>::BSTNode(
    const key_type& key,
    const value_type& value,
    const node_pointer_type& parent,
    const node_pointer_type& left,
    const node_pointer_type& right
) :
    BSTNodeBase<Key, Value>(key, value),
    parent_{parent},
    left_{left},
    right_{right}
{}

template<typename Key, typename Value>
typename BSTNode<Key, Value>::node_pointer_type BSTNode<Key, Value>::getParent() const
{
    return parent_;
}

template<typename Key, typename Value>
typename BSTNode<Key, Value>::node_pointer_type BSTNode<Key, Value>::getLeft() const
{
    return left_;
}

template<typename Key, typename Value>
typename BSTNode<Key, Value>::node_pointer_type BSTNode<Key, Value>::getRight() const
{
    return right_;
}

template<typename Key, typename Value>
typename BSTNode<Key, Value>::node_pointer_type BSTNode<Key, Value>::getPointer() const
{
    return std::make_shared<node_type>(*this);
}

template<typename Key, typename Value>
BSTNode<Key, Value>::operator std::string() const
{
    return BSTNodeBase<Key, Value>::operator std::string() + getLinkString(this);
}

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BSTNode<Key, Value>& node)
{
    os << static_cast<std::string>(node);
    return os;
}
