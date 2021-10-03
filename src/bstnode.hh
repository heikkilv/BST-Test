#ifndef BSTNODE_HH
#define BSTNODE_HH

#include <memory>
#include "bstnode_base.hh"

template<typename Key, typename Value>
class BSTNode : public BSTNodeBase<Key, Value>
{
  public:
    using key_type = typename BSTNodeBase<Key, Value>::key_type;
    using value_type = typename BSTNodeBase<Key, Value>::value_type;
    using node_type = BSTNode<key_type, value_type>;
    using node_pointer_type = std::shared_ptr<node_type>;

    BSTNode();

    BSTNode(
        const key_type& key,
        const value_type& value
    );

    BSTNode(
        const key_type& key,
        const value_type& value,
        const node_pointer_type& parent,
        const node_pointer_type& left,
        const node_pointer_type& right
    );

    node_pointer_type getParent() const;
    node_pointer_type getLeft() const;
    node_pointer_type getRight() const;

    node_pointer_type getPointer() const;

    virtual operator std::string() const override;

  protected:
    node_pointer_type parent_;
    node_pointer_type left_;
    node_pointer_type right_;
};

template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BSTNode<Key, Value>& node);

#include "bstnode.tpp"

#endif // BSTNODE_HH
