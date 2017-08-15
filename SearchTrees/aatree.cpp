// AA tree implementation
//
// Implementation is based on https://en.wikipedia.org/wiki/AA_tree (1.4.2017)
//
// Ville Heikkilä

#ifndef AATREE_CPP
#define AATREE_CPP

#include "aatree.hh"
#include <algorithm>

template<typename Node>
AATree<Node>::AATree() :
    BinarySearchTree<Node>{}
{
}

template<typename Node>
AATree<Node>::~AATree()
{
}

template<typename Node>
bool AATree<Node>::insert(const value_type& value)
{
    if (this->find(value.first) != this->nil_)
    {
        return false;
    }

    Node* node{
        new Node{ value.first, value.second,
                  this->nil_, this->nil_, this->nil_, 1 } };

    if (this->root_ == this->nil_)
    {
        this->root_ = node;
        ++this->nodes_;
    }
    else
    {
        this->root_ = insertNode(node, this->root_);
    }

    return true;
}

template<typename Node>
typename AATree<Node>::size_type AATree<Node>::erase(const key_type& key)
{
    auto node{ this->find(key) };
    if (node == this->nil_)
    {
        return 0;
    }

    --this->nodes_;

    int key1{ node->key_ };

    this->root_ = deleteNode(node, this->root_);

    int key2{ (node != this->nil_) ? node->key_ : key1 - 1 };
    if (key1 == key2)
    {
        delete node;
    }

    return 1;
}

template<typename Node>
Node* AATree<Node>::skew(Node* node)
{
    if (node == this->nil_)
    {
        return this->nil_;
    }
    else if (node->left_ == this->nil_)
    {
        return node;
    }
    else if (node->level_ == node->left_->level_)
    {
        Node* L{ node->left_ };
        node->left_ = L->right_;
        if (node->left_ != this->nil_)
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

template<typename Node>
Node* AATree<Node>::split(Node* node)
{
    if (node == this->nil_)
    {
        return this->nil_;
    }
    else if (node->right_ == this->nil_ or node->right_->right_ == this->nil_)
    {
        return node;
    }
    else if (node->level_ == node->right_->right_->level_)
    {
        Node* R{ node->right_ };
        node->right_ = R->left_;
        if (node->right_ != this->nil_)
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

template<typename Node>
Node* AATree<Node>::insertNode(Node* node, Node* rootNode)
{
    if (node->key_ < rootNode->key_)
    {
        if (rootNode->left_ == this->nil_)
        {
            node->parent_ = rootNode;
            rootNode->left_ = node;
            ++this->nodes_;

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
        if (rootNode->right_ == this->nil_)
        {
            node->parent_ = rootNode;
            rootNode->right_ = node;
            ++this->nodes_;

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

template<typename Node>
Node* AATree<Node>::deleteNode(Node* node, Node* rootNode)
{
    if (rootNode == this->nil_ or node == this->nil_)
    {
        return rootNode;
    }

    if (node == rootNode)
    {
        if (rootNode->left_ == this->nil_ and rootNode->right_ == this->nil_)
        {
            return this->nil_;
        }
        else if (rootNode->left_ == this->nil_)
        {
            Node* L{ this->successor(rootNode) };
            rootNode->right_ = deleteNode(L, rootNode->right_);
            if (rootNode->right_ != this->nil_)
            {
                rootNode->right_->parent_ = rootNode;
            }
            rootNode->key_ = L->key_;
            delete L;
            L = this->nil_;
        }
        else
        {
            Node* L{ this->predecessor(rootNode) };
            rootNode->left_ = deleteNode(L, rootNode->left_);
            if (rootNode->left_ != this->nil_)
            {
                rootNode->left_->parent_ = rootNode;
            }
            rootNode->key_ = L->key_;
            delete L;
            L = this->nil_;
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

    if (rootNode->right_ != this->nil_)
    {
        rootNode->right_->right_ = skew(rootNode->right_->right_);
    }

    rootNode = split(rootNode);
    rootNode->right_ = split(rootNode->right_);

    return rootNode;
}

template<typename Node>
Node* AATree<Node>::decreaseLevel(Node* node)
{
    if (node == this->nil_)
    {
        return this->nil_;
    }

    int leftLevel{ (node->left_ == this->nil_) ? 0 : node->left_->level_ };
    int rightLevel{ (node->right_ == this->nil_) ? 0 : node->right_->level_ };
    int correctLevel{ std::min(leftLevel, rightLevel) + 1 };
    if (correctLevel < node->level_)
    {
        node->level_ = correctLevel;
        if (node->right_ != this->nil_ and correctLevel < node->right_->level_)
        {
            node->right_->level_ = correctLevel;
        }
    }

    return node;
}

#endif // AATREE_CPP
