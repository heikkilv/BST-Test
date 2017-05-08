// AA tree implementation
//
// Implementation is based on https://en.wikipedia.org/wiki/AA_tree (1.4.2017)
//
// Ville Heikkilä

#include "aatree.hh"
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

AATree::AATree() :
    root_{ nullptr },
    nodes_{ 0 }
{
}

AATree::~AATree()
{
    AANode* node{ minimum() };
    while (node != nullptr)
    {
        deleteNode(node);
        node = minimum();
    }
}

int AATree::nodes() const
{
    return nodes_;
}

int AATree::height() const
{
    return height(root_);
}

int AATree::height(AANode* node) const
{
    if (node == nullptr)
    {
        return -1;
    }

    int leftHeight{ (node->left_ == nullptr) ? 0 : height(node->left_) + 1};
    int rightHeight{ (node->right_ == nullptr) ? 0 : height(node->right_) + 1};

    return std::max(leftHeight, rightHeight);
}

void AATree::clear()
{
    AANode* node{ minimum() };
    while (node != nullptr)
    {
        deleteNode(node);
        node = minimum();
    }

    root_ = nullptr;
    nodes_ = 0;
}

AANode* AATree::maximum() const
{
    return maximum(root_);
}

AANode* AATree::maximum(AANode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    AANode* x{ node };
    while (x->right_ != nullptr)
    {
        x = x->right_;
    }
    return x;
}

AANode* AATree::minimum() const
{
    return minimum(root_);
}

AANode* AATree::minimum(AANode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    AANode* x{ node };
    while (x->left_ != nullptr)
    {
        x = x->left_;
    }
    return x;
}

AANode* AATree::successor(AANode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->right_ != nullptr)
    {
        return minimum(node->right_);
    }

    AANode* x{ node };
    AANode* y{ x->parent_ };
    while (y != nullptr and x == y->right_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

AANode* AATree::predecessor(AANode* node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (node->left_ != nullptr)
    {
        return maximum(node->left_);
    }

    AANode* x{ node };
    AANode* y{ x->parent_ };
    while (y != nullptr and x == y->left_)
    {
        x = y;
        y = y->parent_;
    }
    return y;
}

bool AATree::isInTree(AANode* node) const
{
    if (node == nullptr or root_ == nullptr)
    {
        return false;
    }

    AANode* x{ node };
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

AANode* AATree::search(int key) const
{
    AANode* x{ root_ };
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

void AATree::insertNode(AANode* node)
{
    if (node == nullptr)
    {
        return;
    }
    else if (root_ == nullptr)
    {
        root_ = node;
        ++nodes_;
    }
    else
    {
        root_ = insertNode(node, root_);
    }
}

void AATree::deleteNode(AANode* node)
{
    if (not isInTree(node))
    {
        return;
    }

    --nodes_;

    int key1{ node->key_ };

    root_ = deleteNode(node, root_);

    int key2{ (node != nullptr) ? node->key_ : key1 - 1 };
    if (key1 == key2)
    {
        delete node;
    }
}

AANode* AATree::skew(AANode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->left_ == nullptr)
    {
        return node;
    }
    else if (node->level_ == node->left_->level_)
    {
        AANode* L{ node->left_ };
        node->left_ = L->right_;
        if (node->left_ != nullptr)
        {
            node->left_->parent_ = node;
        }
        L->right_ = node;
        L->parent_ = node->parent_;
        L->right_->parent_ = L;
        return L;
    }
    else
    {
        return node;
    }
}

AANode* AATree::split(AANode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (node->right_ == nullptr or node->right_->right_ == nullptr)
    {
        return node;
    }
    else if (node->level_ == node->right_->right_->level_)
    {
        AANode* R{ node->right_ };
        node->right_ = R->left_;
        if (node->right_ != nullptr)
        {
            node->right_->parent_ = node;
        }
        R->left_ = node;
        R->parent_ = node->parent_;
        R->left_->parent_ = R;
        R->level_ += 1;
        return R;
    }
    else
    {
        return node;
    }
}

AANode* AATree::insertNode(AANode* node, AANode* rootNode)
{
    if (node->key_ < rootNode->key_)
    {
        if (rootNode->left_ == nullptr)
        {
            node->parent_ = rootNode;
            rootNode->left_ = node;
            ++nodes_;

            rootNode = skew(rootNode);
            rootNode = split(rootNode);
            return rootNode;
        }
        else
        {
            rootNode->left_ = insertNode(node, rootNode->left_);
        }
    }
    else
    {
        if (rootNode->right_ == nullptr)
        {
            node->parent_ = rootNode;
            rootNode->right_ = node;
            ++nodes_;

            rootNode = skew(rootNode);
            rootNode = split(rootNode);
            return rootNode;
        }
        else
        {
            rootNode->right_ = insertNode(node, rootNode->right_);
        }
    }

    rootNode = skew(rootNode);
    rootNode = split(rootNode);
    return rootNode;
}

AANode* AATree::deleteNode(AANode* node, AANode* rootNode)
{
    if (rootNode == nullptr or node == nullptr)
    {
        return rootNode;
    }

    if (node == rootNode)
    {
        if (rootNode->left_ == nullptr and rootNode->right_ == nullptr)
        {
            return nullptr;
        }
        else if (rootNode->left_ == nullptr)
        {
            AANode* L{ successor(rootNode) };
            rootNode->right_ = deleteNode(L, rootNode->right_);
            if (rootNode->right_ != nullptr)
            {
                rootNode->right_->parent_ = rootNode;
            }
            rootNode->key_ = L->key_;
            delete L;
            L = nullptr;
        }
        else
        {
            AANode* L{ predecessor(rootNode) };
            rootNode->left_ = deleteNode(L, rootNode->left_);
            if (rootNode->left_ != nullptr)
            {
                rootNode->left_->parent_ = rootNode;
            }
            rootNode->key_ = L->key_;
            delete L;
            L = nullptr;
       }
    }
    else if (node->key_ > rootNode->key_)
    {
        rootNode->right_ = deleteNode(node, rootNode->right_);
    }
    else
    {
        rootNode->left_ = deleteNode(node, rootNode->left_);
    }

    rootNode = decreaseLevel(rootNode);
    rootNode = skew(rootNode);
    rootNode->right_ = skew(rootNode->right_);

    if (rootNode->right_ != nullptr)
    {
        rootNode->right_->right_ = skew(rootNode->right_->right_);
    }

    rootNode = split(rootNode);
    rootNode->right_ = split(rootNode->right_);

    return rootNode;
}

AANode* AATree::decreaseLevel(AANode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    int leftLevel{ (node->left_ == nullptr) ? 0 : node->left_->level_ };
    int rightLevel{ (node->right_ == nullptr) ? 0 : node->right_->level_ };
    int correctLevel{ std::min(leftLevel, rightLevel) + 1 };
    if (correctLevel < node->level_)
    {
        node->level_ = correctLevel;
        if (node->right_ != nullptr and correctLevel < node->right_->level_)
        {
            node->right_->level_ = correctLevel;
        }
    }

    return node;
}

void AATree::print() const
{
    const int NODE_WIDTH{ 3 };
    const int NODE_SPACE{ 1 };

    std::vector<AANode*> nodeList;
    int h{ height() };
    for (int level{ 0 }; level <= h; ++level)
    {
        std::vector<AANode*> nodeRow;

        if (level == 0)
        {
            nodeRow.push_back(root_);
        }
        else
        {
            for (unsigned int i{ 0 }; i < nodeList.size(); ++i)
            {
                AANode* x{ nodeList[i] };
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
            std::cout << std::setw(NODE_WIDTH) << std::right;
            if (nodeRow[i] != nullptr)
            {
                if (nodeRow[i]->parent_ != nullptr and
                    nodeRow[i]->level_ == nodeRow[i]->parent_->level_)
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
