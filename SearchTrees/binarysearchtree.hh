// Standard binary search tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 12
//
// Ville Heikkilä

#ifndef BINARYSEARCHTREE_HH
#define BINARYSEARCHTREE_HH

#include <utility>

template<typename Key, typename Value>
struct TreeNode
{
    Key key_;
    Value value_;
    TreeNode<Key, Value>* parent_;
    TreeNode<Key, Value>* left_;
    TreeNode<Key, Value>* right_;
};

template<typename Key, typename Value>
class BinarySearchTree
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = unsigned int;

    BinarySearchTree();
    ~BinarySearchTree();

    size_type size() const;
    int height() const;
    int height(TreeNode<Key, Value>* node) const;

    void clear();

    TreeNode<Key, Value>* maximum() const;
    TreeNode<Key, Value>* maximum(TreeNode<Key, Value>* node) const;
    TreeNode<Key, Value>* minimum() const;
    TreeNode<Key, Value>* minimum(TreeNode<Key, Value>* node) const;

    TreeNode<Key, Value>* successor(TreeNode<Key, Value>* node) const;
    TreeNode<Key, Value>* predecessor(TreeNode<Key, Value>* node) const;

    bool isInTree(TreeNode<Key, Value>* node) const;

    TreeNode<Key, Value>* find(const Key& key) const;
    bool insert(const value_type& value);
    size_type erase(const Key& key);

    void print() const;

private:
    TreeNode<Key, Value>* root_;
    size_type nodes_;

    void transplant(TreeNode<Key, Value>* u, TreeNode<Key, Value>* v);
};

#include "binarysearchtree.cpp"

#endif // BINARYSEARCHTREE_HH
