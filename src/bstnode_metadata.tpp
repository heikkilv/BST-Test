#include "bstnode_metadata.hh"
#include <string>
#include "bstnode_utils.hh"


template<typename Key, typename Value, typename Metadata>
BSTNodeMetadata<Key, Value, Metadata>::BSTNodeMetadata() :
    BSTNodeBase<Key, Value>(),
    metadata_{},
    parent_{nullptr},
    left_{nullptr},
    right_{nullptr}
{}

template<typename Key, typename Value, typename Metadata>
BSTNodeMetadata<Key, Value, Metadata>::BSTNodeMetadata(
    const key_type& key,
    const value_type& value
) :
    BSTNodeBase<Key, Value>(key, value),
    metadata_{},
    parent_{nullptr},
    left_{nullptr},
    right_{nullptr}
{}

template<typename Key, typename Value, typename Metadata>
BSTNodeMetadata<Key, Value, Metadata>::BSTNodeMetadata(
    const key_type& key,
    const value_type& value,
    const metadata_type& metadata
) :
    BSTNodeBase<Key, Value>(key, value),
    metadata_{metadata},
    parent_{nullptr},
    left_{nullptr},
    right_{nullptr}
{}

template<typename Key, typename Value, typename Metadata>
BSTNodeMetadata<Key, Value, Metadata>::BSTNodeMetadata(
    const key_type& key,
    const value_type& value,
    const metadata_type& metadata,
    const node_pointer_type& parent,
    const node_pointer_type& left,
    const node_pointer_type& right
) :
    BSTNodeBase<Key, Value>(key, value),
    metadata_{metadata},
    parent_{parent},
    left_{left},
    right_{right}
{}

template<typename Key, typename Value, typename Metadata>
typename BSTNodeMetadata<Key, Value, Metadata>::metadata_type BSTNodeMetadata<Key, Value, Metadata>::getMetadata() const
{
    return metadata_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNodeMetadata<Key, Value, Metadata>::node_pointer_type BSTNodeMetadata<Key, Value, Metadata>::getParent() const
{
    return parent_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNodeMetadata<Key, Value, Metadata>::node_pointer_type BSTNodeMetadata<Key, Value, Metadata>::getLeft() const
{
    return left_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNodeMetadata<Key, Value, Metadata>::node_pointer_type BSTNodeMetadata<Key, Value, Metadata>::getRight() const
{
    return right_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNodeMetadata<Key, Value, Metadata>::node_pointer_type BSTNodeMetadata<Key, Value, Metadata>::getPointer() const
{
    return std::make_shared<node_type>(*this);
}

template<typename Key, typename Value, typename Metadata>
BSTNodeMetadata<Key, Value, Metadata>::operator std::string() const
{
    return BSTNodeBase<Key, Value>::operator std::string() + getMetadataString(this) + getLinkString(this);
}

template<typename Key, typename Value, typename Metadata>
std::ostream& operator<<(std::ostream& os, const BSTNodeMetadata<Key, Value, Metadata>& node)
{
    os << static_cast<std::string>(node);
    return os;
}
