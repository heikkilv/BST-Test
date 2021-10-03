// Standard binary search tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 12
//
// Ville Heikkilä

#ifndef BINARYSEARCHTREE_CPP
#define BINARYSEARCHTREE_CPP

#include "binarysearchtree.hh"
#include <iomanip>
#include <iostream>
#include <vector>
#include <windows.h>

namespace
{

inline std::ostream& print_white(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

inline std::ostream& print_red(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& print_blue(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
            FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

} // namespace

template<typename Node>
BinarySearchTree<Node>::BinarySearchTree() :
    nil_{ new Node{} },
    root_{ nil_ },
    nodes_{ 0 }
{
}

template<typename Node>
BinarySearchTree<Node>::~BinarySearchTree()
{
    auto node{ minimum() };
    while (node != nil_)
    {
        erase(node->key_);
        node = minimum();
    }
    delete nil_;
}

template<typename Node>
typename BinarySearchTree<Node>::size_type BinarySearchTree<Node>::size() const
{
    return nodes_;
}

template<typename Node>
int BinarySearchTree<Node>::height() const
{
    return height(root_);
}

template<typename Node>
int BinarySearchTree<Node>::height(Node* node) const
{
    if (node == nil_)
    {
        return -1;
    }

    int h{ 0 };
    int hMin{ 0 };
    int hMax{ 0 };

    auto x{ minimum() };
    while (x != nil_)
    {
        if (x->right_ != nil_)
        {
            x = x->right_;
            --h;
            while (x->left_ != nil_)
            {
                x = x->left_;
                --h;
            }
        }
        else
        {
            auto y{ x->parent_ };
            while (y != nil_ and x == y->right_)
            {
                x = y;
                y = y->parent_;
                ++h;
            }
            x = y;
            ++h;
        }

        if (x != nil_ and h > hMax)
        {
            hMax = h;
        }
        if (x != nil_ and h < hMin)
        {
            hMin = h;
        }
    }

    return hMax - hMin;
}

template<typename Node>
void BinarySearchTree<Node>::clear()
{
    auto node{ minimum() };
    while (node != nil_)
    {
        erase(node->key_);
        node = minimum();
    }

    root_ = nil_;
    nodes_ = 0;
}

template<typename Node>
Node* BinarySearchTree<Node>::maximum() const
{
    return maximum(root_);
}

template<typename Node>
Node* BinarySearchTree<Node>::maximum(Node* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    auto x{ node };
    while (x->right_ != nil_)
    {
        x = x->right_;
    }
    return x;
}

template<typename Node>
Node* BinarySearchTree<Node>::minimum() const
{
    return minimum(root_);
}

template<typename Node>
Node* BinarySearchTree<Node>::minimum(Node* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    auto x{ node };
    while (x->left_ != nil_)
    {
        x = x->left_;
    }
    return x;
}

template<typename Node>
Node* BinarySearchTree<Node>::successor(Node* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    if (node->right_ != nil_)
    {
        return minimum(node->right_);
    }

    auto x{ node };
    auto y{ x->parent_ };
    while (y != nil_ and x == y->right_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

template<typename Node>
Node* BinarySearchTree<Node>::predecessor(Node* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    if (node->left_ != nil_)
    {
        return maximum(node->left_);
    }

    auto x{ node };
    auto y{ x->parent_ };
    while (y != nil_ and x == y->left_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

template<typename Node>
bool BinarySearchTree<Node>::isInTree(Node* node) const
{
    if (node == nil_ or root_ == nil_)
    {
        return false;
    }

    auto x{ node };
    while (x != nil_)
    {
        if (x == root_)
        {
            return true;
        }
        x = x->parent_;
    }

    return false;
}

template<typename Node>
Node* BinarySearchTree<Node>::find(const key_type& key) const
{
    auto x{ root_ };
    while (x != nil_)
    {
        if (key < x->key_)
        {
            x = x->left_;
        }
        else if (x->key_ < key)
        {
            x = x->right_;
        }
        else
        {
            return x;
        }
    }
    return x;
}

template<typename Node>
bool BinarySearchTree<Node>::insert(const value_type& value)
{
    Node* x{ root_ };
    Node* parent{ nil_ };

    while (x != nil_)
    {
        parent = x;
        if (value.first < x->key_)
        {
            x = x->left_;
        }
        else if (x->key_ < value.first)
        {
            x = x->right_;
        }
        else
        {
            // Key alreydy exists in the tree
            return false;
        }
    }

    Node* node{
        new Node{ value.first, value.second,
                  parent, nil_, nil_ } };
//    Node* node{ new Node{} };
//    node->key_ = value.first;
//    node->value_ = value.second;
//    node->parent_ = parent;
//    node->left_ = nil_;
//    node->right_ = nil_;

    if (parent == nil_)
    {
        root_ = node;
    }
    else if (node->key_ < parent->key_)
    {
        parent->left_ = node;
    }
    else
    {
        parent->right_ = node;
    }
    ++nodes_;

    return true;
}

template<typename Node>
typename BinarySearchTree<Node>::size_type BinarySearchTree<Node>::erase(const key_type& key)
{
    auto node{ find(key) };
    if (node == nil_)
    {
        return 0;
    }

    if (node->left_ == nil_)
    {
        transplant(node, node->right_);
    }
    else if (node->right_ == nil_)
    {
        transplant(node, node->left_);
    }
    else
    {
        Node* y{ minimum(node->right_) };
        if (y->parent_ != node)
        {
            transplant(y, y->right_);
            y->right_ = node->right_;
            y->right_->parent_ = y;
        }
        transplant(node, y);
        y->left_ = node->left_;
        y->left_->parent_ = y;
    }

    delete node;
    --nodes_;
    return 1;
}

template<typename Node>
void BinarySearchTree<Node>::transplant(Node* u, Node* v)
{
    if (u == nil_)
    {
        return;
    }

    if (u->parent_ == nil_)
    {
        root_ = v;
    }
    else if (u == u->parent_->left_)
    {
        u->parent_->left_ = v;
    }
    else
    {
        u->parent_->right_ = v;
    }

    if (v != nil_)
    {
        v->parent_ = u->parent_;
    }
}

template<typename Node>
void BinarySearchTree<Node>::print() const
{
    const int NODE_WIDTH{ 3 };
    const int NODE_SPACE{ 1 };

    std::vector<Node*> nodeList;
    int h{ height() };
    for (int level{ 0 }; level <= h; ++level)
    {
        std::vector<Node*> nodeRow;

        if (level == 0)
        {
            nodeRow.push_back(root_);
        }
        else
        {
            for (unsigned int i{ 0 }; i < nodeList.size(); ++i)
            {
                Node* x{ nodeList[i] };
                if (x == nil_)
                {
                    nodeRow.push_back(nil_);
                    nodeRow.push_back(nil_);
                }
                else
                {
                    nodeRow.push_back(x->left_);
                    nodeRow.push_back(x->right_);
                }
            }
        }

        int factor{ (NODE_WIDTH+NODE_SPACE)/2 };
        int indent{ factor * ((1 << (h - level)) - 1) };

        if (level > 0)
        {
            bool left{ true };
            for (unsigned int i{ 0 }; i < nodeRow.size(); ++i)
            {

                if (i > 0)
                {
                    std::cout << std::setw(NODE_SPACE) << " ";
                }
                if (indent > 0)
                {
                    std::cout << std::setw(indent) << " ";
                }
                std::cout << std::setw(NODE_WIDTH);
                if (nodeRow[i] != nil_)
                {
                    if (left)
                    {
                        std::cout << std::right << "/";
                    }
                    else
                    {
                        std::cout << std::left << "\\";
                    }
                }
                else
                {
                    std::cout << " ";
                }
                if (i < nodeRow.size() - 1 and indent > 0)
                {
                    std::cout << std::setw(indent) << " ";
                }

                left = not left;
            }
            std::cout << std::endl;
        }

        for (unsigned int i{ 0 }; i < nodeRow.size(); ++i)
        {
            if (i > 0)
            {
                std::cout << std::setw(NODE_SPACE) << " ";
            }
            if (indent > 0)
            {
                std::cout << std::setw(indent) << " ";
            }
            std::cout << std::setw(NODE_WIDTH) << std::right;
            if (nodeRow[i] != nil_)
            {
                if (getPrintColor(nodeRow[i]) == PrintColor::Red)
                {
                    std::cout << print_red;
                }
                else if (getPrintColor(nodeRow[i]) == PrintColor::Blue)
                {
                    std::cout << print_blue;
                }
                std::cout << nodeRow[i]->key_ << print_white;
            }
            else
            {
                std::cout << " ";
            }
            if (i + 1 < nodeRow.size() and indent > 0)
            {
                std::cout << std::setw(indent) << " ";
            }
        }
        std::cout << std::endl;

        nodeList = nodeRow;
    }
}

struct color_failure
{};

template<typename T>
struct color_success : std::true_type
{};

template<>
struct color_success<color_failure> : std::false_type
{};

template<typename T>
struct get_color_result
{
private:
    template<typename X>
    static auto check(X* x) -> decltype(x->getPrintColor());
    static color_failure check(...);
public:
    using type = decltype(check(std::declval<T*>()));
};

template<typename T>
struct has_color : color_success<typename get_color_result<T>::type>
{};

template<typename T>
constexpr bool Has_color()
{
    return has_color<T>::value;
}

template<typename Node, bool C = Has_color<Node>()>
struct ColorStruct
{
    PrintColor color_;
    ColorStruct<Node, C>(Node* node) : color_{ node->getPrintColor() } {}
};

template<typename Node>
struct ColorStruct<Node, false>
{
    PrintColor color_;
    ColorStruct<Node, false>(...) : color_{ PrintColor::White } {}
};

template<typename Node>
PrintColor BinarySearchTree<Node>::getPrintColor(Node* node) const
{
    ColorStruct<Node, Has_color<Node>()> colorStruct{ node };
    return colorStruct.color_;
}

#endif // BINARYSEARCHTREE_CPP
