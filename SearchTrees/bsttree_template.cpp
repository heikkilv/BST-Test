#ifndef BSTTREE_TEMPLATE_CPP
#define BSTTREE_TEMPLATE_CPP

#include "bsttree.hh"
#include <iomanip>
#include <iostream>
#include <vector>

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
BSTTree<Key, Value, Balancer>::BSTTree() :
    nil_{ new node_type{} },
    root_{ nil_ },
    nodes_{ 0 },
    balancer_{ Balancer<Key, Value>(this) }
{
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
BSTTree<Key, Value, Balancer>::~BSTTree()
{
    auto node{ minimum() };
    while (node != nil_)
    {
        erase(node->key_);
        node = minimum();
    }
    delete nil_;
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::size_type BSTTree<Key, Value, Balancer>::size() const
{
    return nodes_;
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
int BSTTree<Key, Value, Balancer>::height() const
{
    return height(root_);
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
void BSTTree<Key, Value, Balancer>::clear()
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::maximum() const
{
    return maximum(root_);
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::minimum() const
{
    return minimum(root_);
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::successor(node_type* node) const
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::predecessor(node_type* node) const
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
bool BSTTree<Key, Value, Balancer>::isInTree(node_type* node) const
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::find(const key_type& key)
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

    balancer_.balanceAfterFind(x);
    return x;
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
bool BSTTree<Key, Value, Balancer>::insert(const value_type& value)
{
    auto x{ root_ };
    auto parent{ nil_ };

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

    node_type* node
    {
        new node_type{ value.first, value.second,
                       balancer_type::getDefaultBalance(),
                       parent, nil_, nil_ }
    };

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

    balancer_.balanceAfterInsert(node);
    return true;
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::size_type BSTTree<Key, Value, Balancer>::erase(const key_type& key)
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
        node_type* y{ minimum(node->right_) };
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

    balancer_.balanceAfterErase(node);
    delete node;
    --nodes_;
    return 1;
}

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
void BSTTree<Key, Value, Balancer>::print() const
{
    const int NODE_WIDTH{ 3 };
    const int NODE_SPACE{ 1 };

    std::vector<node_type*> nodeList;
    int h{ height() };
    for (int level{ 0 }; level <= h; ++level)
    {
        std::vector<node_type*> nodeRow;

        if (level == 0)
        {
            nodeRow.push_back(root_);
        }
        else
        {
            for (unsigned int i{ 0 }; i < nodeList.size(); ++i)
            {
                node_type* x{ nodeList[i] };
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
                std::cout << nodeRow[i]->key_;
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
int BSTTree<Key, Value, Balancer>::height(node_type* node) const
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::maximum(node_type* node) const
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
typename BSTTree<Key, Value, Balancer>::node_type* BSTTree<Key, Value, Balancer>::minimum(node_type* node) const
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

template <typename Key, typename Value, template<typename K, typename V> class Balancer>
void BSTTree<Key, Value, Balancer>::transplant(node_type* u, node_type* v)
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

#endif // BSTTREE_TEMPLATE_CPP
