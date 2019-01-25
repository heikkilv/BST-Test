// Red Black tree implementation
//
// Implementation is based on T.H. Cormen, C.E. Leiserson, R.L. Rivest, C. Stein,
// Introduction to algorithms, 3rd ed. MIT Press, Cambridge, MA, 2009, Chapter 13
//
// Ville Heikkilä

#ifndef REDBLACKTREE_CPP
#define REDBLACKTREE_CPP

#include "redblacktree.hh"

template<typename Node>
RedBlackTree<Node>::RedBlackTree() :
    BinarySearchTree<Node>{}
{
}

template<typename Node>
RedBlackTree<Node>::~RedBlackTree()
{
}

template<typename Node>
bool RedBlackTree<Node>::insert(const value_type& value)
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
            // Key alreydy exists in the tree
            return false;
        }
    }

    Node* node{
        new Node{ value.first, value.second,
                  parent, this->nil_, this->nil_, Color::Red } };

    if (parent == this->nil_)
    {
        this->root_ = node;
    }
    else if (node->key_ < parent->key_)
    {
        parent->left_ = node;
    }
    else
    {
        parent->right_ = node;
    }
    ++this->nodes_;

    insertFix(node);

    return true;
}

template<typename Node>
typename RedBlackTree<Node>::size_type RedBlackTree<Node>::erase(const key_type& key)
{
    auto node{ this->find(key) };
    if (node == this->nil_)
    {
        return 0;
    }

    Node* x{ this->nil_ };
    Node* y{ node };
    Color yOriginalColor{ y->color_ };

    if (node->left_ == this->nil_)
    {
        x = node->right_;
        transplant(node, node->right_);
    }
    else if (node->right_ == this->nil_)
    {
        x = node->left_;
        transplant(node, node->left_);
    }
    else
    {
        Node* y{ this->minimum(node->right_) };
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
    --this->nodes_;

    if (yOriginalColor == Color::Black)
    {
        deleteFix(x);
    }

    return 1;
}

template<typename Node>
void RedBlackTree<Node>::rotateLeft(Node* x)
{
    Node* y{ x->right_ };

    x->right_ = y->left_;
    if (y->left_ != this->nil_)
    {
        y->left_->parent_ = x;
    }

    y->parent_ = x->parent_;
    if (x->parent_ == this->nil_)
    {
        this->root_ = y;
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

template<typename Node>
void RedBlackTree<Node>::rotateRight(Node* x)
{
    Node* y{ x->left_ };

    x->left_ = y->right_;
    if (y->right_ != this->nil_)
    {
        y->right_->parent_ = x;
    }

    y->parent_ = x->parent_;
    if (x->parent_ == this->nil_)
    {
        this->root_ = y;
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

template<typename Node>
void RedBlackTree<Node>::insertFix(Node* x)
{
    while (x->parent_->color_ == Color::Red)
    {
        if (x->parent_ == x->parent_->parent_->left_)
        {
            Node* y{ x->parent_->parent_->right_ };
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
            Node* y{ x->parent_->parent_->left_ };
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

    this->root_->color_ = Color::Black;
}

template<typename Node>
void RedBlackTree<Node>::deleteFix(Node* x)
{
    while (x != this->root_ and x->color_ == Color::Black)
    {
        if (x == x->parent_->left_)
        {
            Node* w = x->parent_->right_;
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
                x = this->root_;
            }
        }
        else
        {
            Node* w = x->parent_->left_;
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
                x = this->root_;
            }
        }
    }

    x->color_ = Color::Black;
}

template<typename Node>
void RedBlackTree<Node>::transplant(Node* u, Node* v)
{
    if (u == this->nil_)
    {
        return;
    }

    if (u->parent_ == this->nil_)
    {
        this->root_ = v;
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

#endif // REDBLACKTREE_CPP
