#include "redblacktree.hh"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>
#include <windows.h>

namespace
{

inline std::ostream& red(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
            FOREGROUND_RED|FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
            FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    return s;
}

} // namespace

RedBlackTree::RedBlackTree() :
    nil_{ new RedBlackNode(-1) },
    root_{ nil_ },
    nodes_{ 0 }
{
}

RedBlackTree::~RedBlackTree()
{
    RedBlackNode* node{ minimum() };
    while (node != nil_)
    {
        deleteNode(node);
        node = minimum();
    }
    delete nil_;
}

int RedBlackTree::nodes() const
{
    return nodes_;
}

int RedBlackTree::height() const
{
    return height(root_);
}

int RedBlackTree::height(RedBlackNode* node) const
{
    if (node == nil_)
    {
        return -1;
    }

    int leftHeight{ (node->left_ == nil_) ? 0 : height(node->left_) + 1};
    int rightHeight{ (node->right_ == nil_) ? 0 : height(node->right_) + 1};

    return std::max(leftHeight, rightHeight);
}

bool RedBlackTree::isNull(RedBlackNode* node) const
{
    return (node == nullptr or node == nil_);
}

void RedBlackTree::clear()
{
    RedBlackNode* node{ minimum() };
    while (node != nil_)
    {
        deleteNode(node);
        node = minimum();
    }

    root_ = nil_;
    nodes_ = 0;
}

RedBlackNode* RedBlackTree::maximum() const
{
    return maximum(root_);
}

RedBlackNode* RedBlackTree::maximum(RedBlackNode* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    RedBlackNode* x{ node };
    while (x->right_ != nil_)
    {
        x = x->right_;
    }
    return x;
}

RedBlackNode* RedBlackTree::minimum() const
{
    return minimum(root_);
}

RedBlackNode* RedBlackTree::minimum(RedBlackNode* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    RedBlackNode* x{ node };
    while (x->left_ != nil_)
    {
        x = x->left_;
    }
    return x;
}

RedBlackNode* RedBlackTree::successor(RedBlackNode* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    if (node->right_ != nil_)
    {
        return minimum(node->right_);
    }

    RedBlackNode* x{ node };
    RedBlackNode* y{ x->parent_ };
    while (y != nil_ and x == y->right_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

RedBlackNode* RedBlackTree::predecessor(RedBlackNode* node) const
{
    if (node == nil_)
    {
        return nil_;
    }

    if (node->left_ != nil_)
    {
        return maximum(node->left_);
    }

    RedBlackNode* x{ node };
    RedBlackNode* y{ x->parent_ };
    while (y != nil_ and x == y->left_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

bool RedBlackTree::isInTree(RedBlackNode* node) const
{
    if (node == nil_ or node == nullptr or root_ == nil_)
    {
        return false;
    }

    RedBlackNode* x{ node };
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

RedBlackNode* RedBlackTree::search(int key) const
{
    RedBlackNode* x{ root_ };
    while (x != nil_ and x->key_ != key)
    {
        if (key < x->key_)
        {
            x = x->left_;
        }
        else
        {
            x = x->right_;
        }
    }
    return x;
}

void RedBlackTree::insertNode(RedBlackNode* node)
{
    if (node == nil_ or node == nullptr)
    {
        return;
    }

    RedBlackNode* x{ root_ };
    RedBlackNode* y{ nil_ };

    while (x != nil_)
    {
        y = x;
        if (node->key_ < x->key_)
        {
            x = x->left_;
        }
        else
        {
            x = x->right_;
        }
    }

    node->parent_ = y;
    ++nodes_;

    if (y == nil_)
    {
        root_ = node;
    }
    else if (node->key_ < y->key_)
    {
        y->left_ = node;
    }
    else
    {
        y->right_ = node;
    }

    node->left_ = nil_;
    node->right_ = nil_;
    node->color_ = Color::Red;
    insertFix(node);
}

void RedBlackTree::deleteNode(RedBlackNode* node)
{
    if (not isInTree(node))
    {
        return;
    }

    RedBlackNode* x{ nil_ };
    RedBlackNode* y{ node };
    Color yOriginalColor{ y->color_ };

    if (node->left_ == nil_)
    {
        x = node->right_;
        transplant(node, node->right_);
    }
    else if (node->right_ == nil_)
    {
        x = node->left_;
        transplant(node, node->left_);
    }
    else
    {
        RedBlackNode* y{ minimum(node->right_) };
        yOriginalColor = y->color_;
        x = y->right_;

        if (y->parent_ == node)
        {
            x->parent_ = y;
        }
        else
        {
            transplant(y, y->right_);
            y->right_ = node->right_;
            y->right_->parent_ = y;
        }
        transplant(node, y);
        y->left_ = node->left_;
        y->left_->parent_ = y;
        y->color_ = node->color_;
    }

    delete node;
    --nodes_;

    if (yOriginalColor == Color::Black)
    {
        deleteFix(x);
    }
}

void RedBlackTree::rotateLeft(RedBlackNode* x)
{
    RedBlackNode* y{ x->right_ };

    x->right_ = y->left_;
    if (y->left_ != nil_)
    {
        y->left_->parent_ = x;
    }

    y->parent_ = x->parent_;
    if (x->parent_ == nil_)
    {
        root_ = y;
    }
    else if (x == x->parent_->left_)
    {
        x->parent_->left_ = y;
    }
    else
    {
        x->parent_->right_ = y;
    }

    y->left_ = x;
    x->parent_ = y;
}

void RedBlackTree::rotateRight(RedBlackNode* x)
{
    RedBlackNode* y{ x->left_ };

    x->left_ = y->right_;
    if (y->right_ != nil_)
    {
        y->right_->parent_ = x;
    }

    y->parent_ = x->parent_;
    if (x->parent_ == nil_)
    {
        root_ = y;
    }
    else if (x == x->parent_->left_)
    {
        x->parent_->left_ = y;
    }
    else
    {
        x->parent_->right_ = y;
    }

    y->right_ = x;
    x->parent_ = y;
}

void RedBlackTree::insertFix(RedBlackNode* x)
{
    while (x->parent_->color_ == Color::Red)
    {
        if (x->parent_ == x->parent_->parent_->left_)
        {
            RedBlackNode* y{ x->parent_->parent_->right_ };
            if (y->color_ == Color::Red)
            {
                x->parent_->color_ = Color::Black;
                y->color_ = Color::Black;
                x->parent_->parent_->color_ = Color::Red;
                x = x->parent_->parent_;
            }
            else
            {
                if (x == x->parent_->right_)
                {
                    x = x->parent_;
                    rotateLeft(x);
                }

                x->parent_->color_ = Color::Black;
                x->parent_->parent_->color_ = Color::Red;
                rotateRight(x->parent_->parent_);
            }
        }
        else
        {
            RedBlackNode* y{ x->parent_->parent_->left_ };
            if (y->color_ == Color::Red)
            {
                x->parent_->color_ = Color::Black;
                y->color_ = Color::Black;
                x->parent_->parent_->color_ = Color::Red;
                x = x->parent_->parent_;
            }
            else
            {
                if (x == x->parent_->left_)
                {
                    x = x->parent_;
                    rotateRight(x);
                }

                x->parent_->color_ = Color::Black;
                x->parent_->parent_->color_ = Color::Red;
                rotateLeft(x->parent_->parent_);
            }
        }
    }

    root_->color_ = Color::Black;
}

void RedBlackTree::deleteFix(RedBlackNode* x)
{
    while (x != root_ and x->color_ == Color::Black)
    {
        if (x == x->parent_->left_)
        {
            RedBlackNode* w = x->parent_->right_;
            if (w->color_ == Color::Red)
            {
                w->color_ = Color::Black;
                x->parent_->color_ = Color::Red;
                rotateLeft(x->parent_);
                w = x->parent_->right_;
            }

            if (w->left_->color_ == Color::Black and w->right_->color_ == Color::Black)
            {
                w->color_ = Color::Red;
                x = x->parent_;
            }
            else
            {
                if (w->right_->color_ == Color::Black)
                {
                    w->left_->color_ = Color::Black;
                    w->color_ = Color::Red;
                    rotateRight(w);
                    w = x->parent_->right_;
                }
                w->color_ = x->parent_->color_;
                x->parent_->color_ = Color::Black;
                w->right_->color_ = Color::Black;
                rotateLeft(x->parent_);
                x = root_;
            }
        }
        else
        {
            RedBlackNode* w = x->parent_->left_;
            if (w->color_ == Color::Red)
            {
                w->color_ = Color::Black;
                x->parent_->color_ = Color::Red;
                rotateRight(x->parent_);
                w = x->parent_->left_;
            }

            if (w->right_->color_ == Color::Black and w->left_->color_ == Color::Black)
            {
                w->color_ = Color::Red;
                x = x->parent_;
            }
            else
            {
                if (w->left_->color_ == Color::Black)
                {
                    w->right_->color_ = Color::Black;
                    w->color_ = Color::Red;
                    rotateLeft(w);
                    w = x->parent_->left_;
                }
                w->color_ = x->parent_->color_;
                x->parent_->color_ = Color::Black;
                w->left_->color_ = Color::Black;
                rotateRight(x->parent_);
                x = root_;
            }
        }
    }

    x->color_ = Color::Black;
}

void RedBlackTree::transplant(RedBlackNode* u, RedBlackNode* v)
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

    v->parent_ = u->parent_;
}

void RedBlackTree::print() const
{
    const int NODE_WIDTH{ 3 };
    const int NODE_SPACE{ 1 };

    std::vector<RedBlackNode*> nodeList;
    int h{ height() };
    for (int level{ 0 }; level <= h; ++level)
    {
        std::vector<RedBlackNode*> nodeRow;

        if (level == 0)
        {
            nodeRow.push_back(root_);
        }
        else
        {
            for (unsigned int i{ 0 }; i < nodeList.size(); ++i)
            {
                RedBlackNode* x{ nodeList[i] };
                if (isNull(x))
                {
                    nodeRow.push_back(nullptr);
                    nodeRow.push_back(nullptr);
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
                if (not isNull(nodeRow[i]))
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
            if (not isNull(nodeRow[i]))
            {
                if (nodeRow[i]->color_ == Color::Red)
                {
                    std::cout << red << nodeRow[i]->key_ << white;
                }
                else
                {
                    std::cout << nodeRow[i]->key_;
                }
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
