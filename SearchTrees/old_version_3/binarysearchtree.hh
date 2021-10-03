// Standard binary search tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 12
//
// Ville Heikkilä

#ifndef BINARYSEARCHTREE_HH
#define BINARYSEARCHTREE_HH

#include <utility>

enum class PrintColor
{
    White,
    Red,
    Blue
};

template<typename Key, typename Value>
struct TreeNode
{
    using key_type = Key;
    using mapped_type = Value;

    key_type key_;
    mapped_type value_;
    TreeNode<key_type, mapped_type>* parent_;
    TreeNode<key_type, mapped_type>* left_;
    TreeNode<key_type, mapped_type>* right_;

    TreeNode() :
        key_{}, value_{},
        parent_{}, left_{}, right_{}
    {}

    TreeNode(const key_type& key, const mapped_type& value,
             TreeNode<key_type, mapped_type>* parent,
             TreeNode<key_type, mapped_type>* left,
             TreeNode<key_type, mapped_type>* right) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right }
    {}
};

template<typename Node>
class BinarySearchTree
{
public:
    using key_type = typename Node::key_type;
    using mapped_type = typename Node::mapped_type;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = unsigned int;
    using node_type = Node;

    BinarySearchTree();
    virtual ~BinarySearchTree();

    virtual size_type size() const;
    virtual int height() const;

    virtual void clear();

    virtual Node* maximum() const;
    virtual Node* minimum() const;

    virtual Node* successor(Node* node) const;
    virtual Node* predecessor(Node* node) const;

    virtual bool isInTree(Node* node) const;

    virtual Node* find(const key_type& key) const;
    virtual bool insert(const value_type& value);
    virtual size_type erase(const key_type& key);

    virtual void print() const;

protected:
    Node* nil_;
    Node* root_;
    size_type nodes_;

    virtual int height(Node* node) const;
    virtual Node* maximum(Node* node) const;
    virtual Node* minimum(Node* node) const;

    PrintColor getPrintColor(Node* node) const;

private:
    void transplant(Node* u, Node* v);
};

#include "binarysearchtree.cpp"

#endif // BINARYSEARCHTREE_HH
