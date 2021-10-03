#ifndef BSTNODE_METADATA_HH
#define BSTNODE_METADATA_HH

#include <memory>
#include "bstnode_base.hh"

template<typename Key, typename Value, typename Metadata>
class BSTNodeMetadata : public BSTNodeBase<Key, Value>
{
  public:
    using key_type = typename BSTNodeBase<Key, Value>::key_type;
    using value_type = typename BSTNodeBase<Key, Value>::value_type;
    using metadata_type = Metadata;
    using node_type = BSTNodeMetadata<key_type, value_type, metadata_type>;
    using node_pointer_type = std::shared_ptr<node_type>;

    BSTNodeMetadata();

    BSTNodeMetadata(
        const key_type& key,
        const value_type& value
    );

    BSTNodeMetadata(
        const key_type& key,
        const value_type& value,
        const metadata_type& metadata
    );

    BSTNodeMetadata(
        const key_type& key,
        const value_type& value,
        const metadata_type& metadata,
        const node_pointer_type& parent,
        const node_pointer_type& left,
        const node_pointer_type& right
    );

    metadata_type getMetadata() const;

    node_pointer_type getParent() const;
    node_pointer_type getLeft() const;
    node_pointer_type getRight() const;

    node_pointer_type getPointer() const;

    virtual operator std::string() const override;

  protected:
    metadata_type metadata_;
    node_pointer_type parent_;
    node_pointer_type left_;
    node_pointer_type right_;
};

template<typename Key, typename Value, typename Metadata>
std::ostream& operator<<(std::ostream& os, const BSTNodeMetadata<Key, Value, Metadata>& node);

#include "bstnode_metadata.tpp"

#endif // BSTNODE_METADATA_HH
