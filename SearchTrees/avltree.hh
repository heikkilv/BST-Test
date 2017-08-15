// AVL tree implementation
//
// Implementation is based on https://bitlush.com/blog/efficient-avl-tree-in-c-sharp (1.4.2017)
//
// Ville Heikkilä

#ifndef AVLTREE_HH
#define AVLTREE_HH

#include "binarysearchtree.hh"
#include <utility>

template<typename Key, typename Value>
struct AVLNode
{
    using key_type = Key;
    using mapped_type = Value;

    key_type key_;
    mapped_type value_;
    AVLNode<key_type, mapped_type>* parent_;
    AVLNode<key_type, mapped_type>* left_;
    AVLNode<key_type, mapped_type>* right_;
    int balance_;

    AVLNode() :
        key_{}, value_{},
        parent_{}, left_{}, right_{},
        balance_{ 0 }
    {}

    AVLNode(const key_type& key, const mapped_type& value,
            AVLNode<key_type, mapped_type>* parent,
            AVLNode<key_type, mapped_type>* left,
            AVLNode<key_type, mapped_type>* right) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right },
        balance_{ 0 }
    {}

    AVLNode(const key_type& key, const mapped_type& value,
            AVLNode<key_type, mapped_type>* parent,
            AVLNode<key_type, mapped_type>* left,
            AVLNode<key_type, mapped_type>* right,
            int balance) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right },
        balance_{ balance }
    {}

    PrintColor getPrintColor()
    {
        if (balance_ < 0)
        {
            return PrintColor::Red;
        }
        else if (balance_ > 0)
        {
            return PrintColor::Blue;
        }
        else
        {
            return PrintColor::White;
        }
    }
};

template<typename Node>
class AVLTree : public BinarySearchTree<Node>
{
public:
    using key_type = typename Node::key_type;
    using mapped_type = typename Node::mapped_type;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = typename BinarySearchTree<Node>::size_type;
    using node_type = Node;

    AVLTree();
    virtual ~AVLTree();

    virtual bool insert(const value_type& value);
    virtual size_type erase(const key_type& key);

private:
    void insertBalance(Node* node, int balance);
    void deleteBalance(Node* node, int balance);
    Node* rotateLeft(Node* x);
    Node* rotateLeftRight(Node* x);
    Node* rotateRight(Node* x);
    Node* rotateRightLeft(Node* x);
    void replace(Node* target, Node* source);
};

#include "avltree.cpp"

#endif // AVLTREE_HH
