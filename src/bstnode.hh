#ifndef BSTNODE_HH
#define BSTNODE_HH

#include <memory>

template<typename Key, typename Value, typename Metadata>
class BSTNode
{
  public:
    using key_type = Key;
    using value_type = Value;
    using metadata_type = Metadata;
    using node_type = BSTNode<key_type, value_type, metadata_type>;
    using node_pointer_type = std::shared_ptr<node_type>;

    BSTNode();

    BSTNode(
        const key_type& key,
        const value_type& value,
        const metadata_type& metadata,
        const node_pointer_type& parent,
        const node_pointer_type& left,
        const node_pointer_type& right
    );

    key_type getKey() const;
    value_type getValue() const;
    metadata_type getMetadata() const;
    node_pointer_type getParent() const;
    node_pointer_type getLeft() const;
    node_pointer_type getRight() const;

    node_pointer_type getPointer() const;

    operator std::string() const;

    friend class BSTTree;

  private:
    key_type key_;
    value_type value_;
    metadata_type metadata_;
    node_pointer_type parent_;
    node_pointer_type left_;
    node_pointer_type right_;
};

template<typename Key, typename Value, typename Metadata>
std::ostream& operator<<(std::ostream& os, const BSTNode<Key, Value, Metadata>& node);

#include "bstnode.tpp"

#endif // BSTNODE_HH
