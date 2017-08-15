// Red Black tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 13
//
// Ville Heikkilä

#ifndef REDBLACKTREE_HH
#define REDBLACKTREE_HH

#include <utility>

enum class Color
{
    Red,
    Black
};

template<typename Key, typename Value>
struct RedBlackNode
{
    Key key_;
    Value value_;
    Color color_;
    RedBlackNode<Key, Value>* parent_;
    RedBlackNode<Key, Value>* left_;
    RedBlackNode<Key, Value>* right_;
};

template<typename Key, typename Value>
class RedBlackTree
{
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = unsigned int;

    RedBlackTree();
    ~RedBlackTree();

    size_type size() const;
    int height() const;
    int height(RedBlackNode<Key, Value>* node) const;
    bool isNull(RedBlackNode<Key, Value>* node) const;

    void clear();

    RedBlackNode<Key, Value>* maximum() const;
    RedBlackNode<Key, Value>* maximum(RedBlackNode<Key, Value>* node) const;
    RedBlackNode<Key, Value>* minimum() const;
    RedBlackNode<Key, Value>* minimum(RedBlackNode<Key, Value>* node) const;

    RedBlackNode<Key, Value>* successor(RedBlackNode<Key, Value>* node) const;
    RedBlackNode<Key, Value>* predecessor(RedBlackNode<Key, Value>* node) const;

    bool isInTree(RedBlackNode<Key, Value>* node) const;

    RedBlackNode<Key, Value>* find(const Key& key) const;
    bool insert(const value_type& value);
    size_type erase(const Key& key);

    void print() const;

private:
    RedBlackNode<Key, Value>* nil_;
    RedBlackNode<Key, Value>* root_;
    size_type nodes_;

    void rotateLeft(RedBlackNode<Key, Value>* x);
    void rotateRight(RedBlackNode<Key, Value>* x);
    void insertFix(RedBlackNode<Key, Value>* x);
    void deleteFix(RedBlackNode<Key, Value>* x);
    void transplant(RedBlackNode<Key, Value>* u, RedBlackNode<Key, Value>* v);
};

#include "redblacktree.cpp"

#endif // REDBLACKTREE_HH
