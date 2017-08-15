// Red Black tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 13
//
// Ville Heikkilä

#ifndef REDBLACKTREE_HH
#define REDBLACKTREE_HH

#include "binarysearchtree.hh"
#include <utility>

enum class Color
{
    Red,
    Black
};

template<typename Key, typename Value>
struct RedBlackNode
{
    using key_type = Key;
    using mapped_type = Value;

    key_type key_;
    mapped_type value_;
    RedBlackNode<key_type, mapped_type>* parent_;
    RedBlackNode<key_type, mapped_type>* left_;
    RedBlackNode<key_type, mapped_type>* right_;
    Color color_;

    RedBlackNode() :
        key_{}, value_{},
        parent_{}, left_{}, right_{},
        color_{ Color::Black }
    {}

    RedBlackNode(const key_type& key, const mapped_type& value,
                 RedBlackNode<key_type, mapped_type>* parent,
                 RedBlackNode<key_type, mapped_type>* left,
                 RedBlackNode<key_type, mapped_type>* right) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right },
        color_{ Color::Black }
    {}

    RedBlackNode(const key_type& key, const mapped_type& value,
                 RedBlackNode<key_type, mapped_type>* parent,
                 RedBlackNode<key_type, mapped_type>* left,
                 RedBlackNode<key_type, mapped_type>* right,
                 Color color) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right },
        color_{ color }
    {}

    PrintColor getPrintColor()
    {
        return (color_ == Color::Red) ? PrintColor::Red : PrintColor::White;
    }
};

template<typename Node>
class RedBlackTree : public BinarySearchTree<Node>
{
public:
    using key_type = typename Node::key_type;
    using mapped_type = typename Node::mapped_type;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = typename BinarySearchTree<Node>::size_type;
    using node_type = Node;

    RedBlackTree();
    virtual ~RedBlackTree();

    virtual bool insert(const value_type& value);
    virtual size_type erase(const key_type& key);

private:
    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void insertFix(Node* x);
    void deleteFix(Node* x);
    void transplant(Node* u, Node* v);
};

#include "redblacktree.cpp"

#endif // REDBLACKTREE_HH
