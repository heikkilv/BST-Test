// AA tree implementation
//
// Implementation is based on https://en.wikipedia.org/wiki/AA_tree (1.4.2017)
//
// Ville Heikkilä

#ifndef AATREE_HH
#define AATREE_HH

#include <utility>

template<typename Key, typename Value>
struct AANode
{
    Key key_;
    Value value_;
    int level_;
    AANode<Key, Value>* parent_;
    AANode<Key, Value>* left_;
    AANode<Key, Value>* right_;
};

template<typename Key, typename Value>
class AATree
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = unsigned int;

    AATree();
    ~AATree();

    size_type size() const;
    int height() const;
    int height(AANode<Key, Value>* node) const;

    void clear();

    AANode<Key, Value>* maximum() const;
    AANode<Key, Value>* maximum(AANode<Key, Value>* node) const;
    AANode<Key, Value>* minimum() const;
    AANode<Key, Value>* minimum(AANode<Key, Value>* node) const;

    AANode<Key, Value>* successor(AANode<Key, Value>* node) const;
    AANode<Key, Value>* predecessor(AANode<Key, Value>* node) const;

    bool isInTree(AANode<Key, Value>* node) const;

    AANode<Key, Value>* find(const Key& key) const;
    bool insert(const value_type& value);
    size_type erase(const Key& key);

    void print() const;

private:
    AANode<Key, Value>* root_;
    size_type nodes_;

    AANode<Key, Value>* skew(AANode<Key, Value>* node);
    AANode<Key, Value>* split(AANode<Key, Value>* node);
    AANode<Key, Value>* insertNode(AANode<Key, Value>* node, AANode<Key, Value>* rootNode);
    AANode<Key, Value>* deleteNode(AANode<Key, Value>* node, AANode<Key, Value>* rootNode);
    AANode<Key, Value>* decreaseLevel(AANode<Key, Value>* node);
};

#include "aatree.cpp"

#endif // AATREE_HH
