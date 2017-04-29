#include "binarysearchtree.hh"
#include <iomanip>
#include <iostream>
#include <vector>

BinarySearchTree::BinarySearchTree() :
    root_{ nullptr },
    nodes_{ 0 }
{
}

BinarySearchTree::~BinarySearchTree()
{
    TreeNode* node{ minimum() };
    while (node != nullptr)
    {
        deleteNode(node);
        node = minimum();
    }
}

int BinarySearchTree::nodes() const
{
    return nodes_;
}

int BinarySearchTree::height() const
{
    return height(root_);
}

int BinarySearchTree::height(TreeNode* node) const
{
    if (node == nullptr)
    {
        return -1;
    }

    int h{ 0 };
    int hMin{ 0 };
    int hMax{ 0 };

    TreeNode* x{ minimum() };
    while (x != nullptr)
    {
        if (x->right_ != nullptr)
        {
            x = x->right_;
            --h;
            while (x->left_ != nullptr)
            {
                x = x->left_;
                --h;
            }
        }
        else
        {
            TreeNode* y{ x->parent_ };
            while (y != nullptr and x == y->right_)
            {
                x = y;
                y = y->parent_;
                ++h;
            }
            x = y;
            ++h;
        }

        if (x != nullptr and h > hMax)
        {
            hMax = h;
        }
        if (x != nullptr and h < hMin)
        {
            hMin = h;
        }
    }

    return hMax - hMin;
}

void BinarySearchTree::clear()
{
    TreeNode* node{ minimum() };
    while (node != nullptr)
    {
        deleteNode(node);
        node = minimum();
    }

    root_ = nullptr;
    nodes_ = 0;
}

TreeNode* BinarySearchTree::maximum() const
{
    return maximum(root_);
}

TreeNode* BinarySearchTree::maximum(TreeNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    TreeNode* x{ node };
    while (x->right_ != nullptr)
    {
        x = x->right_;
    }
    return x;
}

TreeNode* BinarySearchTree::minimum() const
{
    return minimum(root_);
}

TreeNode* BinarySearchTree::minimum(TreeNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    TreeNode* x{ node };
    while (x->left_ != nullptr)
    {
        x = x->left_;
    }
    return x;
}

TreeNode* BinarySearchTree::successor(TreeNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right_ != nullptr)
    {
        return minimum(node->right_);
    }

    TreeNode* x{ node };
    TreeNode* y{ x->parent_ };
    while (y != nullptr and x == y->right_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

TreeNode* BinarySearchTree::predecessor(TreeNode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->left_ != nullptr)
    {
        return maximum(node->left_);
    }

    TreeNode* x{ node };
    TreeNode* y{ x->parent_ };
    while (y != nullptr and x == y->left_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

bool BinarySearchTree::isInTree(TreeNode* node) const
{
    if (node == nullptr or root_ == nullptr)
    {
        return false;
    }

    TreeNode* x{ node };
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

TreeNode* BinarySearchTree::search(int key) const
{
    TreeNode* x{ root_ };
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

void BinarySearchTree::insertNode(TreeNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    TreeNode* x{ root_ };
    TreeNode* y{ nullptr };

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
    }
    else if (node->key_ < y->key_)
    {
        y->left_ = node;
    }
    else
    {
        y->right_ = node;
    }
}

void BinarySearchTree::deleteNode(TreeNode* node)
{
    if (not isInTree(node))
    {
        return;
    }

    if (node->left_ == nullptr)
    {
        transplant(node, node->right_);
    }
    else if (node->right_ == nullptr)
    {
        transplant(node, node->left_);
    }
    else
    {
        TreeNode* y{ minimum(node->right_) };
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
}

void BinarySearchTree::transplant(TreeNode* u, TreeNode* v)
{
    if (u == nullptr)
    {
        return;
    }

    if (u->parent_ == nullptr)
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

    if (v != nullptr)
    {
        v->parent_ = u->parent_;
    }
}

void BinarySearchTree::print() const
{
    const int NODE_WIDTH{ 3 };
    const int NODE_SPACE{ 1 };

    std::vector<TreeNode*> nodeList;
    int h{ height() };
    for (int level{ 0 }; level <= h; ++level)
    {
        std::vector<TreeNode*> nodeRow;

        if (level == 0)
        {
            nodeRow.push_back(root_);
        }
        else
        {
            for (unsigned int i{ 0 }; i < nodeList.size(); ++i)
            {
                TreeNode* x{ nodeList[i] };
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
                std::cout << std::right << nodeRow[i]->key_;
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
