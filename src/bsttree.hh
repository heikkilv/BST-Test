#ifndef BSTTREE_HH
#define BSTTREE_HH

#include "bstnode.hh"
#include <utility>

template <typename Key, typename Value, template<typename Key, typename Value> class Balancer>
class BSTTree
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using balancer_type = Balancer<Key, Value>;
    using value_type = std::pair<const key_type, mapped_type>;
    using node_type = BSTNode<Key, Value, typename balancer_type::balance_type>;
    using size_type = unsigned int;

    BSTTree();
    ~BSTTree();

    size_type size() const;
    int height() const;

    void clear();

    node_type* maximum() const;
    node_type* minimum() const;

    node_type* successor(node_type* node) const;
    node_type* predecessor(node_type* node) const;

    bool isInTree(node_type* node) const;

    node_type* find(const key_type& key);
    bool insert(const value_type& value);
    size_type erase(const key_type& key);

    void print() const;

private:
    node_type* nil_;
    node_type* root_;
    size_type nodes_;
    balancer_type balancer_;

    int height(node_type* node) const;
    node_type* maximum(node_type* node) const;
    node_type* minimum(node_type* node) const;

    void transplant(node_type* u, node_type* v);
};

#include "bsttree.tpp"

#endif // BSTTREE_HH
