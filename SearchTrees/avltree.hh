// AVL tree implementation
//
// Implementation is based on https://bitlush.com/blog/efficient-avl-tree-in-c-sharp (1.4.2017)
//
// Ville Heikkilä

#ifndef AVLTREE_HH
#define AVLTREE_HH

#include <utility>

template<typename Key, typename Value>
struct AVLNode
{
    Key key_;
    Value value_;
    int balance_;
    AVLNode<Key, Value>* parent_;
    AVLNode<Key, Value>* left_;
    AVLNode<Key, Value>* right_;
};

template<typename Key, typename Value>
class AVLTree
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = unsigned int;

    AVLTree();
    ~AVLTree();

    size_type size() const;
    int height() const;
    int height(AVLNode<Key, Value>* node) const;

    void clear();

    AVLNode<Key, Value>* maximum() const;
    AVLNode<Key, Value>* maximum(AVLNode<Key, Value>* node) const;
    AVLNode<Key, Value>* minimum() const;
    AVLNode<Key, Value>* minimum(AVLNode<Key, Value>* node) const;

    AVLNode<Key, Value>* successor(AVLNode<Key, Value>* node) const;
    AVLNode<Key, Value>* predecessor(AVLNode<Key, Value>* node) const;

    bool isInTree(AVLNode<Key, Value>* node) const;

    AVLNode<Key, Value>* find(const Key& key) const;
    bool insert(const value_type& value);
    size_type erase(const Key& key);

    void print() const;

private:
    AVLNode<Key, Value>* root_;
    size_type nodes_;

    void insertBalance(AVLNode<Key, Value>* node, int balance);
    void deleteBalance(AVLNode<Key, Value>* node, int balance);
    AVLNode<Key, Value>* rotateLeft(AVLNode<Key, Value>* x);
    AVLNode<Key, Value>* rotateLeftRight(AVLNode<Key, Value>* x);
    AVLNode<Key, Value>* rotateRight(AVLNode<Key, Value>* x);
    AVLNode<Key, Value>* rotateRightLeft(AVLNode<Key, Value>* x);
    void replace(AVLNode<Key, Value>* target, AVLNode<Key, Value>* source);
};

#include "avltree.cpp"

#endif // AVLTREE_HH
