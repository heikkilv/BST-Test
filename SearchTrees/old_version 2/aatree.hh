// AA tree implementation
//
// Implementation is based on https://en.wikipedia.org/wiki/AA_tree (1.4.2017)
//
// Ville Heikkilä

#ifndef AATREE_HH
#define AATREE_HH

#include "binarysearchtree.hh"
#include <utility>

template<typename Key, typename Value>
struct AANode
{
    using key_type = Key;
    using mapped_type = Value;
    const static int DEFAULT_LEVEL = 1;
    const static int NULL_LEVEL = -10;

    key_type key_;
    mapped_type value_;
    AANode<key_type, mapped_type>* parent_;
    AANode<key_type, mapped_type>* left_;
    AANode<key_type, mapped_type>* right_;
    int level_;

    AANode() :
        key_{}, value_{},
        parent_{}, left_{}, right_{},
        level_{ NULL_LEVEL }
    {}

    AANode(const key_type& key, const mapped_type& value,
           AANode<key_type, mapped_type>* parent,
           AANode<key_type, mapped_type>* left,
           AANode<key_type, mapped_type>* right) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right },
        level_{ DEFAULT_LEVEL }
    {}

    AANode(const key_type& key, const mapped_type& value,
            AANode<key_type, mapped_type>* parent,
            AANode<key_type, mapped_type>* left,
            AANode<key_type, mapped_type>* right,
            int level) :
        key_{ key }, value_{ value },
        parent_{ parent }, left_{ left }, right_{ right },
        level_{ level }
    {}

    PrintColor getPrintColor()
    {
        if (level_ != NULL_LEVEL and parent_ != nullptr and
            parent_->level_ != NULL_LEVEL and level_ == parent_->level_)
        {
            return PrintColor::Red;
        }
        else
        {
            return PrintColor::White;
        }
    }
};

template<typename Node>
class AATree : public BinarySearchTree<Node>
{
public:
    using key_type = typename Node::key_type;
    using mapped_type = typename Node::mapped_type;
    using value_type = std::pair<const key_type, mapped_type>;
    using size_type = typename BinarySearchTree<Node>::size_type;
    using node_type = Node;

    AATree();
    virtual ~AATree();

    virtual bool insert(const value_type& value);
    virtual size_type erase(const key_type& key);

private:
    Node* skew(Node* node);
    Node* split(Node* node);
    Node* insertNode(Node* node, Node* rootNode);
    Node* deleteNode(Node* node, Node* rootNode);
    Node* decreaseLevel(Node* node);
};

#include "aatree.cpp"

#endif // AATREE_HH
