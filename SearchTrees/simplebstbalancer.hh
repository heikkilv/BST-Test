#ifndef SIMPLEBSTBALANCER_HH
#define SIMPLEBSTBALANCER_HH

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
class BSTTree;

template<typename Key, typename Value, typename BalanceType>
class BSTNode;

template<typename Key, typename Value>
class SimpleBSTBalancer
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using balance_type = bool;

    using tree_type = BSTTree<key_type, mapped_type, SimpleBSTBalancer>;
    using node_type = BSTNode<key_type, mapped_type, balance_type>;

    static const balance_type DEFAULT_BALANCE = false;

    SimpleBSTBalancer(tree_type* tree) :
        tree_{ tree }
    {}

    SimpleBSTBalancer(SimpleBSTBalancer&& balancer) :
        tree_ { balancer.tree_ }
    {}

    ~SimpleBSTBalancer()
    {
    }

    static balance_type getDefaultBalance()
    {
        return false;
    }

    void balanceAfterFind(node_type*)
    {
    }

    void balanceAfterInsert(node_type*)
    {
    }

    void balanceAfterErase(node_type*)
    {
    }

private:
    tree_type* tree_;

    SimpleBSTBalancer(const SimpleBSTBalancer&) = delete;
    SimpleBSTBalancer& operator=(const SimpleBSTBalancer&) = delete;
    SimpleBSTBalancer& operator=(SimpleBSTBalancer&&) = delete;
};

#endif // SIMPLEBSTBALANCER_HH
