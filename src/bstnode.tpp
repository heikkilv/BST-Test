#include "bstnode.hh"
#include <string>
#include <fmt/core.h>


template<typename Key, typename Value, typename Metadata>
BSTNode<Key, Value, Metadata>::BSTNode() :
    key_{},
    value_{},
    metadata_{},
    parent_{nullptr},
    left_{nullptr},
    right_{nullptr}
{}

template<typename Key, typename Value, typename Metadata>
BSTNode<Key, Value, Metadata>::BSTNode(
    const key_type& key,
    const value_type& value,
    const metadata_type& metadata,
    const node_pointer_type& parent,
    const node_pointer_type& left,
    const node_pointer_type& right
) :
    key_{key},
    value_{value},
    metadata_{metadata},
    parent_{parent},
    left_{left},
    right_{right}
{}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::key_type BSTNode<Key, Value, Metadata>::getKey() const
{
    return key_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::value_type BSTNode<Key, Value, Metadata>::getValue() const
{
    return value_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::metadata_type BSTNode<Key, Value, Metadata>::getMetadata() const
{
    return metadata_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getParent() const
{
    return parent_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getLeft() const
{
    return left_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getRight() const
{
    return right_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getPointer() const
{
    return std::make_shared<BSTNode<Key, Value, Metadata>>(*this);
}

template<typename Key, typename Value, typename Metadata>
BSTNode<Key, Value, Metadata>::operator std::string() const
{
    std::string valueString = fmt::format(
        "{} -> {}, ({})",
        key_,
        value_,
        metadata_
    );

    if (parent_ != nullptr)
    {
        valueString += fmt::format(", P: ({})", parent_->key_);
    }
    if (left_ != nullptr)
    {
        valueString += fmt::format(", L: ({})", left_->key_);
    }
    if (right_ != nullptr)
    {
        valueString += fmt::format(", R: ({})", right_->key_);
    }

    return valueString;
}

template<typename Key, typename Value, typename Metadata>
std::ostream& operator<<(std::ostream& os, const BSTNode<Key, Value, Metadata>& node)
{
    os << static_cast<std::string>(node);
    return os;
}
