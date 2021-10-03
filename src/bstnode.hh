#ifndef BSTNODE_HH
#define BSTNODE_HH

#include <memory>

template<typename Key, typename Value, typename BalanceType>
class BSTNode
{
  public:
    using key_type = Key;
    using mapped_type = Value;
    using balance_type = BalanceType;
    using node_type = BSTNode<key_type, mapped_type, balance_type>;
    using node_type_pointer = std::unique_ptr<node_type>;

    key_type key_;
    mapped_type value_;
    balance_type balance_;
    node_type_pointer parent_;
    node_type_pointer left_;
    node_type_pointer right_;

    BSTNode() :
        key_{},
        value_{},
        balance_{},
        parent_{nullptr},
        left_{nullptr},
        right_{nullptr}
    {}

    BSTNode(const key_type& key,
            const mapped_type& value,
            const balance_type& balance,
            node_type_pointer parent,
            node_type_pointer left,
            node_type_pointer right) :
        key_{key},
        value_{value},
        balance_{balance},
        parent_{parent},
        left_{left},
        right_{right}
    {}
};

#endif // BSTNODE_HH
