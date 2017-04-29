#include "avltree.hh"
#include <iomanip>
#include <iostream>
#include <vector>
#include <windows.h>

namespace
{

inline std::ostream& blue(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
            FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    return s;
}

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

AVLTree::AVLTree() :
    root_{ nullptr },
    nodes_{ 0 }
{
}

void printNodeInfo(AVLNode* node)
{
    std::cout << "key: " << node->key_ << " ";
    if (node->left_ != nullptr)
        std::cout << "left: " << node->left_->key_ << " ";
    if (node->right_ != nullptr)
        std::cout << "right: " << node->right_->key_ << " ";
    if (node->parent_ != nullptr)
        std::cout << "parent: " << node->parent_->key_ << " ";
    std::cout << std::endl;
}

void printAllNodes(AVLNode* node)
{
    if (node != nullptr)
    {
        printNodeInfo(node);
        printAllNodes(node->left_);
        printAllNodes(node->right_);
    }
}

AVLTree::~AVLTree()
{
    AVLNode* node{ minimum() };
    while (node != nullptr)
    {
        deleteNode(node);
        node = minimum();
    }
}

int AVLTree::nodes() const
{
    return nodes_;
}

int AVLTree::height() const
{
    return height(root_);
}

int AVLTree::height(AVLNode* node) const
{
    if (node == nullptr)
    {
        return -1;
    }

    int leftHeight{ node->left_ == nullptr ? 0 : height(node->left_) + 1 };
    int rightHeight{ node->right_ == nullptr ? 0 : height(node->right_) + 1 };

    return std::max(leftHeight, rightHeight);
}

void AVLTree::clear()
{
    AVLNode* node{ minimum() };
    while (node != nullptr)
    {
        deleteNode(node);
        node = minimum();
    }

    root_ = nullptr;
    nodes_ = 0;
}

AVLNode* AVLTree::maximum() const
{
    return maximum(root_);
}

AVLNode* AVLTree::maximum(AVLNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    AVLNode* x{ node };
    while (x->right_ != nullptr)
    {
        x = x->right_;
    }
    return x;
}

AVLNode* AVLTree::minimum() const
{
    return minimum(root_);
}

AVLNode* AVLTree::minimum(AVLNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    AVLNode* x{ node };
    while (x->left_ != nullptr)
    {
        x = x->left_;
    }
    return x;
}

AVLNode* AVLTree::successor(AVLNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right_ != nullptr)
    {
        return minimum(node->right_);
    }

    AVLNode* x{ node };
    AVLNode* y{ x->parent_ };
    while (y != nullptr and x == y->right_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

AVLNode* AVLTree::predecessor(AVLNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->left_ != nullptr)
    {
        return maximum(node->left_);
    }

    AVLNode* x{ node };
    AVLNode* y{ x->parent_ };
    while (y != nullptr and x == y->left_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

bool AVLTree::isInTree(AVLNode* node) const
{
    if (node == nullptr or root_ == nullptr)
    {
        return false;
    }

    AVLNode* x{ node };
    while (x != nullptr)
    {
        if (x == root_)
        {
            return true;
        }
        x = x->parent_;
    }

    return false;
}

AVLNode* AVLTree::search(int key) const
{
    AVLNode* x{ root_ };
    while (x != nullptr and x->key_ != key)
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

void AVLTree::insertNode(AVLNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    AVLNode* x{ root_ };
    AVLNode* y{ nullptr };

    while (x != nullptr)
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

    if (y == nullptr)
    {
        root_ = node;
        root_->balance_ = 0;
    }
    else if (node->key_ < y->key_)
    {
        y->left_ = node;
        insertBalance(y, 1);
    }
    else
    {
        y->right_ = node;
        insertBalance(y, -1);
    }
}

void AVLTree::deleteNode(AVLNode* node)
{
    if (not isInTree(node))
    {
        return;
    }

    AVLNode* left{ node->left_ };
    AVLNode* right{ node->right_ };

    if (left == nullptr)
    {
        if (right == nullptr)
        {
            if (node == root_)
            {
                delete root_;
                root_ = nullptr;
            }
            else
            {
                if (node->parent_->left_ == node)
                {
                    node->parent_->left_ = nullptr;
                    deleteBalance(node->parent_, -1);
                    delete node;
                }
                else
                {
                    node->parent_->right_ = nullptr;
                    deleteBalance(node->parent_, 1);
                    delete node;
                }
            }
        }
        else
        {
            replace(node, right);
            deleteBalance(node, 0);
        }
    }
    else if (right == nullptr)
    {
        replace(node, left);
        deleteBalance(node, 0);
    }
    else
    {
        AVLNode* successor{ right };
        if (successor->left_ == nullptr)
        {
            successor->parent_ = node->parent_;
            successor->left_ = left;
            successor->balance_ = node->balance_;

            if (left != nullptr)
            {
                left->parent_ = successor;
            }

            if (node == root_)
            {
                root_ = successor;
            }
            else
            {
                if (node->parent_->left_ == node)
                {
                    node->parent_->left_ = successor;
                }
                else
                {
                    node->parent_->right_ = successor;
                }
            }

            deleteBalance(successor, 1);
            delete node;
        }
        else
        {
            while (successor->left_ != nullptr)
            {
                successor = successor->left_;
            }

            AVLNode* successorParent{ successor->parent_ };
            AVLNode* successorRight{ successor->right_ };

            if (successorParent->left_ == successor)
            {
                successorParent->left_ = successorRight;
            }
            else
            {
                successorParent->right_ = successorRight;
            }

            if (successorRight != nullptr)
            {
                successorRight->parent_ = successorParent;
            }

            successor->parent_ = node->parent_;
            successor->left_ = left;
            successor->balance_ = node->balance_;
            successor->right_ = right;
            right->parent_ = successor;

            if (left != nullptr)
            {
                left->parent_ = successor;
            }

            if (node == root_)
            {
                root_ = successor;
            }
            else
            {
                if (node->parent_->left_ == node)
                {
                    node->parent_->left_ = successor;
                }
                else
                {
                    node->parent_->right_ = successor;
                }
            }

            deleteBalance(successorParent, -1);
            delete node;
        }
    }

    --nodes_;
}

void AVLTree::insertBalance(AVLNode* node, int balance)
{
    while (node != nullptr)
    {
        node->balance_ += balance;
        balance = node->balance_;

        if (balance == 0)
        {
            return;
        }
        else if (balance == 2)
        {
            if (node->left_->balance_ == 1)
            {
                rotateRight(node);
            }
            else
            {
                rotateLeftRight(node);
            }

            return;
        }
        else if (balance == -2)
        {
            if (node->right_->balance_ == -1)
            {
                rotateLeft(node);
            }
            else
            {
                rotateRightLeft(node);
            }

            return;
        }

        if (node->parent_ != nullptr)
        {
            balance = (node->parent_->left_ == node) ? 1 : -1;
        }

        node = node->parent_;
    }
}

AVLNode* AVLTree::rotateLeft(AVLNode* node)
{
    AVLNode* right{ node->right_ };
    AVLNode* rightleft{ right->left_ };
    AVLNode* parent{ node->parent_ };

    right->parent_ = parent;
    right->left_ = node;
    node->right_ = rightleft;
    node->parent_ = right;

    if (rightleft != nullptr)
    {
        rightleft->parent_ = node;
    }

    if (node == root_)
    {
        root_ = right;
    }
    else if (parent->right_ == node)
    {
        parent->right_ = right;
    }
    else
    {
        parent->left_ = right;
    }

    ++right->balance_;
    node->balance_ = -right->balance_;

    return right;
}

AVLNode* AVLTree::rotateRight(AVLNode* node)
{
    AVLNode* left{ node->left_ };
    AVLNode* leftright{ left->right_ };
    AVLNode* parent{ node->parent_ };

    left->parent_ = parent;
    left->right_ = node;
    node->left_ = leftright;
    node->parent_ = left;

    if (leftright != nullptr)
    {
        leftright->parent_ = node;
    }

    if (node == root_)
    {
        root_ = left;
    }
    else if (parent->left_ == node)
    {
        parent->left_ = left;
    }
    else
    {
        parent->right_ = left;
    }

    --left->balance_;
    node->balance_ = -left->balance_;

    return left;
}

AVLNode* AVLTree::rotateLeftRight(AVLNode* node)
{
    AVLNode* left{ node->left_ };
    AVLNode* leftright{ left->right_ };
    AVLNode* parent{ node->parent_ };
    AVLNode* leftrightleft = leftright->left_;
    AVLNode* leftrightright = leftright->right_;

    leftright->parent_ = parent;
    node->left_ = leftrightright;
    left->right_ = leftrightleft;
    leftright->left_ = left;
    leftright->right_ = node;
    left->parent_ = leftright;
    node->parent_ = leftright;

    if (leftrightright != nullptr)
    {
        leftrightright->parent_ = node;
    }

    if (leftrightleft != nullptr)
    {
        leftrightleft->parent_ = left;
    }

    if (node == root_)
    {
        root_ = leftright;
    }
    else if (parent->left_ == node)
    {
        parent->left_ = leftright;
    }
    else
    {
        parent->right_ = leftright;
    }

    if (leftright->balance_ == -1)
    {
        node->balance_ = 0;
        left->balance_ = 1;
    }
    else if (leftright->balance_ == 0)
    {
        node->balance_ = 0;
        left->balance_ = 0;
    }
    else
    {
        node->balance_ = -1;
        left->balance_ = 0;
    }

    leftright->balance_ = 0;

    return leftright;
}

AVLNode* AVLTree::rotateRightLeft(AVLNode* node)
{
    AVLNode* right{ node->right_ };
    AVLNode* rightleft{ right->left_ };
    AVLNode* parent{ node->parent_ };
    AVLNode* rightleftleft = rightleft->left_;
    AVLNode* rightleftright = rightleft->right_;

    rightleft->parent_ = parent;
    node->right_ = rightleftleft;
    right->left_ = rightleftright;
    rightleft->right_ = right;
    rightleft->left_ = node;
    right->parent_ = rightleft;
    node->parent_ = rightleft;

    if (rightleftleft != nullptr)
    {
        rightleftleft->parent_ = node;
    }

    if (rightleftright != nullptr)
    {
        rightleftright->parent_ = right;
    }

    if (node == root_)
    {
        root_ = rightleft;
    }
    else if (parent->right_ == node)
    {
        parent->right_ = rightleft;
    }
    else
    {
        parent->left_ = rightleft;
    }

    if (rightleft->balance_ == 1)
    {
        node->balance_ = 0;
        right->balance_ = -1;
    }
    else if (rightleft->balance_ == 0)
    {
        node->balance_ = 0;
        right->balance_ = 0;
    }
    else
    {
        node->balance_ = 1;
        right->balance_ = 0;
    }

    rightleft->balance_ = 0;

    return rightleft;
}

void AVLTree::deleteBalance(AVLNode* node, int balance)
{
    while (node != nullptr)
    {
        node->balance_ += balance;
        balance = node->balance_;

        if (balance == 2)
        {
            if (node->left_->balance_ >= 0)
            {
                node = rotateRight(node);

                if (node->balance_ == -1)
                {
                    return;
                }
            }
            else
            {
                node = rotateLeftRight(node);
            }
        }
        else if (balance == -2)
        {
            if (node->right_->balance_ <= 0)
            {
                node = rotateLeft(node);

                if (node->balance_ == 1)
                {
                    return;
                }
            }
            else
            {
                node = rotateRightLeft(node);
            }
        }
        else if (balance != 0)
        {
            return;
        }

        if (node->parent_ != nullptr)
        {
            balance = (node->parent_->left_ == node) ? -1 : 1;
        }

        node = node->parent_;
    }
}

void AVLTree::replace(AVLNode* target, AVLNode* source)
{
    target->balance_ = source->balance_;
    target->key_ = source->key_;
    target->left_ = source->left_;
    target->right_ = source->right_;

    if (source->left_ != nullptr)
    {
        source->left_->parent_ = target;
    }

    if (source->right_ != nullptr)
    {
        source->right_->parent_ = target;
    }

    delete source;
}

void AVLTree::print() const
{
    const int NODE_WIDTH{ 3 };
    const int NODE_SPACE{ 1 };

    std::vector<AVLNode*> nodeList;
    int h{ height() };
    for (int level{ 0 }; level <= h; ++level)
    {
        std::vector<AVLNode*> nodeRow;

        if (level == 0)
        {
            nodeRow.push_back(root_);
        }
        else
        {
            for (unsigned int i{ 0 }; i < nodeList.size(); ++i)
            {
                AVLNode* x{ nodeList[i] };
                if (x == nullptr)
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
                if (nodeRow[i] != nullptr)
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
            std::cout << std::setw(NODE_WIDTH);
            if (nodeRow[i] != nullptr)
            {
                std::cout << std::setw(NODE_WIDTH) <<std::right;
                if (nodeRow[i]->balance_ == -1)
                {
                    std::cout << red << nodeRow[i]->key_ << white;
                }
                else if (nodeRow[i]->balance_ == 1)
                {
                    std::cout << blue << nodeRow[i]->key_ << white;
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
