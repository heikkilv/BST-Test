#ifndef BSTNODE_HH
#define BSTNODE_HH

template<typename Key, typename Value, typename BalanceType>
class BSTNode
{
  public:
    using key_type = Key;
    using mapped_type = Value;
    using balance_type = BalanceType;
    using node_type = BSTNode<key_type, mapped_type, balance_type>;

    key_type key_;
    mapped_type value_;
    balance_type balance_;
    node_type* parent_;
    node_type* left_;
    node_type* right_;

    BSTNode() :
        key_{},
        value_{},
        balance_{},
        parent_{ nullptr },
        left_{ nullptr },
        right_{ nullptr }
    {}

    BSTNode(const key_type& key,
            const mapped_type& value,
            const balance_type& balance,
            node_type* parent,
            node_type* left,
            node_type* right) :
        key_{ key },
        value_{ value },
        balance_{ balance },
        parent_{ parent },
        left_{ left },
        right_{ right }
    {}
};

#endif // BSTNODE_HH
