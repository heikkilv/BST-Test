#include "bstnode.hh"

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
typename BSTNode<Key, Value, Metadata>::key_type BSTNode<Key, Value, Metadata>::getKey() {
    return key_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::value_type BSTNode<Key, Value, Metadata>::getValue() {
    return value_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::metadata_type BSTNode<Key, Value, Metadata>::getMetadata() {
    return metadata_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getParent() {
    return parent_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getLeft() {
    return left_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getRight() {
    return right_;
}

template<typename Key, typename Value, typename Metadata>
typename BSTNode<Key, Value, Metadata>::node_pointer_type BSTNode<Key, Value, Metadata>::getPointer() {
    return std::make_shared<BSTNode<Key, Value, Metadata>>(*this);
}
