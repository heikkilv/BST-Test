// AVL tree implementation
//
// Implementation is based on https://bitlush.com/blog/efficient-avl-tree-in-c-sharp (1.4.2017)
//
// Ville Heikkilä

#ifndef AVLTREE_CPP
#define AVLTREE_CPP

#include "avltree.hh"

template<typename Node>
AVLTree<Node>::AVLTree() :
    BinarySearchTree<Node>{}
{
}

template<typename Node>
AVLTree<Node>::~AVLTree()
{
}

template<typename Node>
bool AVLTree<Node>::insert(const value_type& value)
{
    Node* x{ this->root_ };
    Node* parent{ this->nil_ };

    while (x != this->nil_)
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
            return false;
        }
    }

    Node* node{
        new Node{ value.first, value.second,
                  parent, this->nil_, this->nil_, 0 } };

    ++this->nodes_;

    if (parent == this->nil_)
    {
        this->root_ = node;
    }
    else if (node->key_ < parent->key_)
    {
        parent->left_ = node;
        insertBalance(parent, 1);
    }
    else
    {
        parent->right_ = node;
        insertBalance(parent, -1);
    }

    return true;
}

template<typename Node>
typename AVLTree<Node>::size_type AVLTree<Node>::erase(const key_type& key)
{
    auto node{ this->find(key) };
    if (node == this->nil_)
    {
        return 0;
    }

    Node* left{ node->left_ };
    Node* right{ node->right_ };

    if (left == this->nil_)
    {
        if (right == this->nil_)
        {
            if (node == this->root_)
            {
                delete this->root_;
                this->root_ = this->nil_;
            }
            else
            {
                if (node->parent_->left_ == node)
                {
                    node->parent_->left_ = this->nil_;
                    deleteBalance(node->parent_, -1);
                    delete node;
                }
                else
                {
                    node->parent_->right_ = this->nil_;
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
    else if (right == this->nil_)
    {
        replace(node, left);
        deleteBalance(node, 0);
    }
    else
    {
        Node* successor{ right };
        if (successor->left_ == this->nil_)
        {
            successor->parent_ = node->parent_;
            successor->left_ = left;
            successor->balance_ = node->balance_;

            if (left != this->nil_)
            {
                left->parent_ = successor;
            }

            if (node == this->root_)
            {
                this->root_ = successor;
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
            while (successor->left_ != this->nil_)
            {
                successor = successor->left_;
            }

            Node* successorParent{ successor->parent_ };
            Node* successorRight{ successor->right_ };

            if (successorParent->left_ == successor)
            {
                successorParent->left_ = successorRight;
            }
            else
            {
                successorParent->right_ = successorRight;
            }

            if (successorRight != this->nil_)
            {
                successorRight->parent_ = successorParent;
            }

            successor->parent_ = node->parent_;
            successor->left_ = left;
            successor->balance_ = node->balance_;
            successor->right_ = right;
            right->parent_ = successor;

            if (left != this->nil_)
            {
                left->parent_ = successor;
            }

            if (node == this->root_)
            {
                this->root_ = successor;
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

    --this->nodes_;
    return 1;
}

template<typename Node>
void AVLTree<Node>::insertBalance(Node* node, int balance)
{
    while (node != this->nil_)
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

        if (node->parent_ != this->nil_)
        {
            balance = (node->parent_->left_ == node) ? 1 : -1;
        }

        node = node->parent_;
    }
}

template<typename Node>
Node* AVLTree<Node>::rotateLeft(Node* node)
{
    Node* right{ node->right_ };
    Node* rightleft{ right->left_ };
    Node* parent{ node->parent_ };

    right->parent_ = parent;
    right->left_ = node;
    node->right_ = rightleft;
    node->parent_ = right;

    if (rightleft != this->nil_)
    {
        rightleft->parent_ = node;
    }

    if (node == this->root_)
    {
        this->root_ = right;
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

template<typename Node>
Node* AVLTree<Node>::rotateRight(Node* node)
{
    Node* left{ node->left_ };
    Node* leftright{ left->right_ };
    Node* parent{ node->parent_ };

    left->parent_ = parent;
    left->right_ = node;
    node->left_ = leftright;
    node->parent_ = left;

    if (leftright != this->nil_)
    {
        leftright->parent_ = node;
    }

    if (node == this->root_)
    {
        this->root_ = left;
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

template<typename Node>
Node* AVLTree<Node>::rotateLeftRight(Node* node)
{
    Node* left{ node->left_ };
    Node* leftright{ left->right_ };
    Node* parent{ node->parent_ };
    Node* leftrightleft = leftright->left_;
    Node* leftrightright = leftright->right_;

    leftright->parent_ = parent;
    node->left_ = leftrightright;
    left->right_ = leftrightleft;
    leftright->left_ = left;
    leftright->right_ = node;
    left->parent_ = leftright;
    node->parent_ = leftright;

    if (leftrightright != this->nil_)
    {
        leftrightright->parent_ = node;
    }

    if (leftrightleft != this->nil_)
    {
        leftrightleft->parent_ = left;
    }

    if (node == this->root_)
    {
        this->root_ = leftright;
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

template<typename Node>
Node* AVLTree<Node>::rotateRightLeft(Node* node)
{
    Node* right{ node->right_ };
    Node* rightleft{ right->left_ };
    Node* parent{ node->parent_ };
    Node* rightleftleft = rightleft->left_;
    Node* rightleftright = rightleft->right_;

    rightleft->parent_ = parent;
    node->right_ = rightleftleft;
    right->left_ = rightleftright;
    rightleft->right_ = right;
    rightleft->left_ = node;
    right->parent_ = rightleft;
    node->parent_ = rightleft;

    if (rightleftleft != this->nil_)
    {
        rightleftleft->parent_ = node;
    }

    if (rightleftright != this->nil_)
    {
        rightleftright->parent_ = right;
    }

    if (node == this->root_)
    {
        this->root_ = rightleft;
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

template<typename Node>
void AVLTree<Node>::deleteBalance(Node* node, int balance)
{
    while (node != this->nil_)
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

        if (node->parent_ != this->nil_)
        {
            balance = (node->parent_->left_ == node) ? -1 : 1;
        }

        node = node->parent_;
    }
}

template<typename Node>
void AVLTree<Node>::replace(Node* target, Node* source)
{
    target->balance_ = source->balance_;
    target->key_ = source->key_;
    target->left_ = source->left_;
    target->right_ = source->right_;

    if (source->left_ != this->nil_)
    {
        source->left_->parent_ = target;
    }

    if (source->right_ != this->nil_)
    {
        source->right_->parent_ = target;
    }

    delete source;
}

#endif // AVTREE_CPP
